
using System;
using System.Text;

using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using System.Collections.Generic;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Producto_calcularValoracionMedia) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class ProductoCP : BasicCP
{
public void CalcularValoracionMedia (int p_oid)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Producto_calcularValoracionMedia) ENABLED START*/

        IProductoCAD productoCAD = null;
        ProductoCEN productoCEN = null;



        try
        {
                SessionInitializeTransaction ();
                productoCAD = new ProductoCAD (session);
                productoCEN = new  ProductoCEN (productoCAD);



                // Write here your custom transaction ...

                throw new NotImplementedException ("Method CalcularValoracionMedia() not yet implemented.");



                SessionCommit ();
        }
        catch (Exception ex)
        {
                SessionRollBack ();
                throw ex;
        }
        finally
        {
                SessionClose ();
        }


        /*PROTECTED REGION END*/
}
}
}
