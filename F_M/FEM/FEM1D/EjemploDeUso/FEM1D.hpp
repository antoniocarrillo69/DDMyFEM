//////////////////////////////////////////////////////////////////////////////////////////////
// Clase para el m�todo de elemento finito                                                  //
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


#ifndef __FEM1D__
#define __FEM1D__


#include "F_M.hpp"
#include "MatrizBand.hpp"
#include "Problema_1D.hpp"
#include "Geometria_1D.hpp"



/// Clase para resolver problemas en una dimensi�n por el m�todo elemento finito
/** @author Antonio Carrillo Ledesma
    @date verano 2009
    @version 1.0.1
    @bug No hay errores conocidos
*/
class FEM1D : public F_M
{
private:

   /// Puntero a la definicion del problema
   Problema_1D   *Pr;
   /// Puntero a la definicion de la geometria
   Geometria_1D  *Ge;


public:

   /// Constructor de la clase
   /** @param pr Puntero a la definici�n del problema en una dimensi�n
       @param ge Puntero a la definici�n de la geometria eb una dimensi�n
       @param rsl Puntero a la definici�n del resolvedor de sistemas lineales  */
   FEM1D(Problema_1D *pr, Geometria_1D *ge, ResuelveSistemaLineal *rsl) : F_M(pr,ge,rsl)
   {
      Pr = pr;
      Ge = ge;

      banda = 3;
      solicitaMemoria();
   }


   /// Establece las condiciones de frontera
   void estableceCondicionesFrontera(void);

   /// Genera el sistema lineal asociado al problema
   void generaSistemaLineal(void);

};

/**
Esta clase implementa los comportamientos para resolver un problema en una dimensi�n
@example EjemploFEM1D.cpp */

#endif
