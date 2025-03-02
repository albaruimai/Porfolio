
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Pedido_devolverPedido) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class PedidoCP : BasicCP
{
public void DevolverPedido (int p_oid, string p_descripcion, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum p_motivo, int p_usuario)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Pedido_devolverPedido) ENABLED START*/

        IPedidoCAD pedidoCAD = null;
        PedidoCEN pedidoCEN = null;

        DevolucionCAD devolucionCAD = null;
        DevolucionCEN devolucionCEN = null;




        try
        {
                SessionInitializeTransaction ();
                devolucionCAD = new DevolucionCAD (session);
                devolucionCEN = new DevolucionCEN (devolucionCAD);

                pedidoCAD = new PedidoCAD (session);
                pedidoCEN = new  PedidoCEN (pedidoCAD);
                PedidoEN pedidoEN = pedidoCEN.ReadOID (p_oid);

                pedidoEN.Estado = Enumerated.Roll_n_Run.EstadoEnum.enDevolucion;
                pedidoCAD.ModifyDefault (pedidoEN);

                int idDev = devolucionCEN.New_ (p_descripcion, p_motivo, p_oid, p_usuario);
                //DevolucionEN devEN = devolucionCEN.ReadOID(idDev);
                //devolucionCAD.ModifyDefault(devEN);

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
