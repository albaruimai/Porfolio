
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_modify) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class ValoracionCP : BasicCP
{
public void Modify (int p_Valoracion_OID, double p_valor, string p_comentario, int p_producto)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Valoracion_modify) ENABLED START*/

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


                ValoracionEN valoracionAntigua = valoracionCEN.ReadOID (p_Valoracion_OID);


                ProductoEN prodEn = productoCEN.ReadOID (p_producto);


                ValoracionEN valoracionEN = null;
                //Initialized ValoracionEN
                valoracionEN = new ValoracionEN ();
                valoracionEN.Id = p_Valoracion_OID;
                valoracionEN.Valor = p_valor;
                valoracionEN.Comentario = p_comentario;
                int cont_val = 0;
                double sum_val = 0;
                foreach (ValoracionEN val in valoracionCAD.GetValoracionesProducto (p_producto)) {
                        cont_val++;
                        sum_val = sum_val + val.Valor;
                }
                sum_val = sum_val - valoracionAntigua.Valor + p_valor;

                prodEn.Val_media = sum_val / cont_val;
                //Call to ValoracionCAD

                valoracionCAD.Modify (valoracionEN);


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
