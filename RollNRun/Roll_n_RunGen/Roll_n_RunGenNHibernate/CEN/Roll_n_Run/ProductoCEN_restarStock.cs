
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


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_restarStock) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class ProductoCEN
{
public void RestarStock (int p_oid, int p_cantidad)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_restarStock) ENABLED START*/

        ProductoEN productoEN = _IProductoCAD.ReadOIDDefault (p_oid);
        ProductoCEN productoCEN = new ProductoCEN ();

        if (p_cantidad > 0 && productoCEN.HayStock (p_oid, p_cantidad)) {
                productoEN.Stock = productoEN.Stock - p_cantidad;
                _IProductoCAD.ModifyDefault (productoEN);
                Console.WriteLine ("Se ha disminuido exitosamente el Stock en '" + p_cantidad + "'.");
        }

        else{
                Console.WriteLine ("Ha habido un fallo con el valor '" + p_cantidad + "' o no hay suficiente stock.");
        }

        /*PROTECTED REGION END*/
}
}
}
