
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_destroy) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class ValoracionCP : BasicCP
{
public void Destroy (int p_Valoracion_OID)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_destroy) ENABLED START*/

        IValoracionCAD valoracionCAD = null;
        ValoracionCEN valoracionCEN = null;

        IProductoCAD productoCAD = null;
        ProductoCEN productoCEN = null;


        try
        {
                SessionInitializeTransaction ();
                valoracionCAD = new ValoracionCAD (session);
                valoracionCEN = new  ValoracionCEN (valoracionCAD);
                productoCAD = new ProductoCAD (session);
                productoCEN = new ProductoCEN (productoCAD);


                ValoracionEN valoracionEN = valoracionCEN.ReadOID (p_Valoracion_OID);

                ProductoEN productoEN = productoCEN.ReadOID (valoracionEN.Producto.Id);


                int cont_val = 0;
                double sum_val = 0;
                foreach (ValoracionEN val in valoracionCAD.GetValoracionesProducto (valoracionEN.Producto.Id)) {
                        cont_val++;
                        sum_val = sum_val + val.Valor;
                }
                cont_val--;
                sum_val = sum_val - valoracionEN.Valor;
                if (cont_val > 0) {
                        productoEN.Val_media = sum_val / cont_val;
                }
                else{
                        productoEN.Val_media = 0;
                }
                productoCAD.ModifyDefault (productoEN);

                valoracionCAD.Destroy (p_Valoracion_OID);


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
