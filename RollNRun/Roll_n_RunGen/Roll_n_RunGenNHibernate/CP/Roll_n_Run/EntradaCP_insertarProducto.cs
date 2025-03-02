
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_insertarProducto) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class EntradaCP : BasicCP
{
public void InsertarProducto (int p_producto, int p_oid)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Entrada_insertarProducto) ENABLED START*/

        IEntradaCAD entradaCAD = null;
        EntradaCEN entradaCEN = null;

        ProductoCAD productoCAD = null;
        ProductoCEN productoCEN = null;



        try
        {
                SessionInitializeTransaction ();
                entradaCAD = new EntradaCAD (session);
                entradaCEN = new  EntradaCEN (entradaCAD);

                productoCAD = new ProductoCAD ();
                productoCEN = new ProductoCEN (productoCAD);

                EntradaEN entradaEN = entradaCEN.ReadOID (p_oid);

                entradaEN.Producto = productoCEN.ReadOID (p_producto);;

                entradaCAD.Modify (entradaEN);


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
