
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_new_) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class ValoracionCP : BasicCP
{
public Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN New_ (double p_valor, string p_comentario, int p_producto, int p_usuario)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_new_) ENABLED START*/

        IValoracionCAD valoracionCAD = null;
        ValoracionCEN valoracionCEN = null;

        IProductoCAD productoCAD = null;
        ProductoCEN productoCEN = null;

        Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN result = null;


        try
        {
                SessionInitializeTransaction ();
                valoracionCAD = new ValoracionCAD (session);
                valoracionCEN = new ValoracionCEN (valoracionCAD);
                productoCAD = new ProductoCAD (session);
                productoCEN = new ProductoCEN (productoCAD);




                int oid;
                //Initialized ValoracionEN
                ValoracionEN valoracionEN;
                valoracionEN = new ValoracionEN ();
                valoracionEN.Valor = p_valor;

                valoracionEN.Comentario = p_comentario;


                if (p_producto != -1) {
                        valoracionEN.Producto = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN ();
                        valoracionEN.Producto.Id = p_producto;
                }


                if (p_usuario != -1) {
                        valoracionEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                        valoracionEN.Usuario.Id = p_usuario;
                }

                //Call to ValoracionCAD

                oid = valoracionCAD.New_ (valoracionEN);
                result = valoracionCAD.ReadOIDDefault (oid);


                ProductoEN productoEN = productoCEN.ReadOID (valoracionEN.Producto.Id);

                int cont_val = 0;
                double sum_val = 0;
                foreach (ValoracionEN val in valoracionCAD.GetValoracionesProducto (valoracionEN.Producto.Id)) {
                        cont_val++;
                        sum_val = sum_val + val.Valor;
                }
                productoEN.Val_media = sum_val / cont_val;




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
        return result;


        /*PROTECTED REGION END*/
}
}
}
