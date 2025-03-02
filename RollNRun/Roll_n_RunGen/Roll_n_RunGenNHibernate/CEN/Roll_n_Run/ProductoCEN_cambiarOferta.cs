
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


/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_cambiarOferta) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
public partial class ProductoCEN
{
public void CambiarOferta (int p_oid, double val_oferta)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CEN.Roll_n_Run_Producto_cambiarOferta) ENABLED START*/

        // Write here your custom code...

        ProductoEN productoEN = _IProductoCAD.ReadOIDDefault (p_oid);

        if (productoEN.Oferta != val_oferta) {
                productoEN.Oferta = val_oferta;
                _IProductoCAD.ModifyDefault (productoEN);
                Console.WriteLine ("Se ha cambiado exitosamente la oferta del producto a " + val_oferta);
        }

        else{
                Console.WriteLine ("Ha habido un problema con la oferta, o es la misma que el valor actual.");
        }


        /*PROTECTED REGION END*/
}
}
}
