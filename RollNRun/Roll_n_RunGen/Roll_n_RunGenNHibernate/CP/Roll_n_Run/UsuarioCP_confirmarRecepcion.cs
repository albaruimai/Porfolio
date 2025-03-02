
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Usuario_confirmarRecepcion) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class UsuarioCP : BasicCP
{
public void ConfirmarRecepcion (int p_oid, int p_pedido)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Usuario_confirmarRecepcion) ENABLED START*/

        PedidoCAD pedidoCAD = null;
        PedidoCEN pedidoCEN = null;


        try
        {
                SessionInitializeTransaction ();

                pedidoCAD = new PedidoCAD (session);
                pedidoCEN = new PedidoCEN (pedidoCAD);
                PedidoEN pedidoEN = pedidoCEN.ReadOID (p_pedido);

                pedidoEN.Estado = Enumerated.Roll_n_Run.EstadoEnum.recibido;

                pedidoCAD.ModifyDefault (pedidoEN);

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
