//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para integrar una funcion mediante la cuadratura Gauss-Legendre usando de          //
// 2 a 10 puntos                                                                            //
//                                                                                          //
// An�lisis y Dise�o y Programaci�n:                                                        //
//                                                                                          //
// Nombre:   Antonio Carrillo Ledesma                                                       //
// E-mail:   acl@www.mmc.geofisica.unam.mx                                                  //
// P�gina:   http://www.mmc.geofisica.unam.mx/acl                                           //
//                                                                                          //
//                                                                                          //
// Este programa es software libre. Puede redistribuirlo y/o modificarlo                    //
// bajo los t�rminos de la Licencia P�blica General de GNU seg�n es                         //
// publicada por la Free Software Foundation, bien de la versi�n 2 de                       //
// dicha Licencia o bien (seg�n su elecci�n) de cualquier versi�n                           //
// posterior.                                                                               //
//                                                                                          //
// Este programa se distribuye con la esperanza de que sea �til, pero SIN                   //
// NINGUNA GARANT�A, incluso sin la garant�a MERCANTIL impl�cita o sin                      //
// garantizar la CONVENIENCIA PARA UN PROP�SITO PARTICULAR. V�ase la                        //
// Licencia P�blica General de GNU para m�s detalles.                                       //
//                                                                                          //
// Deber�a haber recibido una copia de la Licencia P�blica General junto                    //
// con este programa. Si no ha sido as�, escriba a la Free Software                         //
// Foundation, Inc., en 675 Mass Ave, Cambridge, MA 02139, EEUU.                            //
//                                                                                          //
//                                                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////


#include <stdio.h>
#include "GaussQuad.hpp"

// Arreglo para las Xi donde deber� ser evaluada la funci�n
static ldouble PUNTOS[][10] =
{
   {0.577350269189625764509148780502,-0.577350269189625764509148780502,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.774596669241483377035853079956,0.0,-0.774596669241483377035853079956,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.861136311594052575223946488893,0.339981043584856264802665759103,-0.339981043584856264802665759103,-0.861136311594052575223946488893,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.906179845938663992797626878299,0.538469310105683091036314420700,0.0,-0.538469310105683091036314420700,-0.906179845938663992797626878299,0.0,0.0,0.0,0.0,0.0},
   {0.932469514203152027812301554494,0.661209386466264513661399595020,0.238619186083196908630501721681,-0.238619186083196908630501721681,-0.661209386466264513661399595020,-0.932469514203152027812301554494,0.0,0.0,0.0,0.0},
   {0.949107912342758524526189684048,0.741531185599394439863864773281,0.405845151377397166906606412077,0.0,-0.405845151377397166906606412077,-0.741531185599394439863864773281,-0.949107912342758524526189684048,0.0,0.0,0.0},
   {0.960289856497536231683560868569,0.796666477413626739591553936476,0.525532409916328985817739049189,0.183434642495649804939476142360,-0.183434642495649804939476142360,-0.525532409916328985817739049189,-0.796666477413626739591553936476,-0.960289856497536231683560868569,0.0,0.0},
   {0.968160239507626089835576202904,0.836031107326635794299429788070,0.613371432700590397308702039341,0.324253423403808929038538014643,0.0,-0.324253423403808929038538014643,-0.613371432700590397308702039341,-0.836031107326635794299429788070,-0.968160239507626089835576202904,0.0},
   {0.973906528517171720077964012084,0.865063366688984510732096688423,0.679409568299024406234327365115,0.433395394129247190799265943166,0.148874338981631210884626001130,-0.148874338981631210884626001130,-0.433395394129247190799265943166,-0.679409568299024406234327365115,-0.865063366688984510732096688423,-0.973906528517171720077964012084}
};

// Arreglo para los pesos que ser�n multiplicados por los valores de la funci�n para obtener la integraci�n
static ldouble PESOS[][10] =
{
   {1.0,1.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.555555555555555555555555555556,0.888888888888888888888888888889,0.555555555555555555555555555556,0.0,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.347854845137453857373063949222,0.652145154862546142626936050778,0.652145154862546142626936050778,0.347854845137453857373063949222,0.0,0.0,0.0,0.0,0.0,0.0},
   {0.236926885056189087514264040720,0.478628670499366468041291514836,0.568888888888888888888888888889,0.478628670499366468041291514836,0.236926885056189087514264040720,0.0,0.0,0.0,0.0,0.0},
   {0.171324492379170345040296142173,0.360761573048138607569833513838,0.467913934572691047389870343990,0.467913934572691047389870343990,0.360761573048138607569833513838,0.171324492379170345040296142173,0.0,0.0,0.0,0.0},
   {0.129484966168869693270611432679,0.279705391489276667901467771424,0.381830050505118944950369775489,0.417959183673469387755102040816,0.381830050505118944950369775489,0.279705391489276667901467771424,0.129484966168869693270611432679,0.0,0.0,0.0},
   {0.101228536290376259152531354310,0.222381034453374470544355994426,0.313706645877887287337962201987,0.36268378337836198297,0.362683783378361982965150449277,0.313706645877887287337962201987,0.222381034453374470544355994426,0.101228536290376259152531354310,0.0,0.0},
   {0.0812743883615744119718921581105,0.180648160694857404058472031243,0.260610696402935462318742869419,0.312347077040002840068630406584,0.330239355001259763164525069287,0.312347077040002840068630406584,0.260610696402935462318742869419,0.180648160694857404058472031243,0.0812743883615744119718921581105,0.0},
   {0.0666713443086881375935688098933,0.149451349150580593145776339658,0.219086362515982043995534934228,0.269266719309996355091226921569,0.295524224714752870173892994651,0.295524224714752870173892994651,0.269266719309996355091226921569,0.219086362515982043995534934228,0.149451349150580593145776339658,0.0666713443086881375935688098933}
};



// Constructor
GaussQuad::GaussQuad(ldouble a, ldouble b, int n, ldouble *x)
{
   this->a = a;
   this->b = b;
   np = n;
#ifdef DEPURAR
   if (n < 2 || n > 10)
   {
      printf("\nUsar Puntos de Integracion Gausianos [2-10]\n");
      np = 10;
   }
#endif
   puntosCalcular(x);
}


// Constructor
GaussQuad::GaussQuad(ldouble a, ldouble b, int n, ldouble *x, ldouble *w)
{
   this->a = a;
   this->b = b;
   np = n;
#ifdef DEPURAR
   if (n < 2 || n > 10)
   {
      printf("\nUsar Puntos de Integracion Gausianos [2-10]\n");
      np = 10;
   }
#endif
   puntosCalcular(x);
   pesosCalcular(w);
}


// Calcula la integral a partir de los puntos de F que fueron evaluados en los puntos X
ldouble GaussQuad::integra(ldouble f[])
{
   ldouble integral;
   int j;

   integral = 0.0;

   for (j = 0; j < np; j++)
   {
      integral += PESOS[np-2][j] * f[j] * ((b - a) / 2.0);
   }

   return integral;
}


// Calcula los puntos sobre los que se debera calcular F para realizar la integracion
void GaussQuad::puntosCalcular(ldouble *x)
{
   int j;

   for (j = 0; j < np; j++)
   {
      x[j] = ((b - a)  * PUNTOS[np-2][j] + (b + a)) / 2.0;
   }
}

// Calcula los puntos sobre los que se debera calcular F para realizar la integracion
void GaussQuad::pesosCalcular(ldouble *w)
{
   int j;

   for (j = 0; j < np; j++)
   {
      w[j] = PESOS[np-2][j] * ((b - a) / 2.0);
   }
}

