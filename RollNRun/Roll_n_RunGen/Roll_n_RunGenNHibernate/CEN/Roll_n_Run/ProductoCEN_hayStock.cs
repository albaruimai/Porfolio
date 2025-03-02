
using System;
using System.Text;
using System.Collections.Generic;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using Roll_n_RunGenNHibernate.Exceptions;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_hayStock) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class ProductoCEN
{
public bool HayStock (int p_oid, int p_cantidad)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_hayStock) ENABLED START*/

        ProductoEN productoEN = _IProductoCAD.ReadOIDDefault (p_oid);

        //La cantidad es el numero de ese producto que se quiere restar del stock total
        //Comprobamos si la cantidad es MAYOR a cero y MENOR O IGUAL que el stock actual y se lo restamos
        if (p_cantidad > 0 && p_cantidad <= productoEN.Stock) {
                Console.WriteLine ("Hay suficiente stock para la cantidad de '" + p_cantidad + "'.");
                return true;
        }

        else{
                Console.WriteLine ("No es un valor correcto o no hay suficiente stock para la cantidad de '" + p_cantidad + "'.");
                return false;
        }
        /*PROTECTED REGION END*/
}
}
}
