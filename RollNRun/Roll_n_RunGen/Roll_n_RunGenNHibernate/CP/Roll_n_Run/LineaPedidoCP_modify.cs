
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_LineaPedido_modify) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class LineaPedidoCP : BasicCP
{
public void Modify (int p_LineaPedido_OID, int p_cantidad, double p_precio)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_LineaPedido_modify) ENABLED START*/

        ILineaPedidoCAD lineaPedidoCAD = null;
        LineaPedidoCEN lineaPedidoCEN = null;


        PedidoCAD pedidoCAD = null;
        PedidoCEN pedidoCEN = null;



        try
        {
                SessionInitializeTransaction ();

                pedidoCAD = new PedidoCAD (session);
                pedidoCEN = new PedidoCEN (pedidoCAD);

                lineaPedidoCAD = new LineaPedidoCAD (session);
                lineaPedidoCEN = new  LineaPedidoCEN (lineaPedidoCAD);




                LineaPedidoEN lineaPedidoEN = null;
                //Initialized LineaPedidoEN
                lineaPedidoEN = new LineaPedidoEN ();
                lineaPedidoEN.Id = p_LineaPedido_OID;
                double restar = lineaPedidoEN.Precio * lineaPedidoEN.Cantidad;

                lineaPedidoEN.Cantidad = p_cantidad;
                lineaPedidoEN.Precio = p_precio;
                //Call to LineaPedidoCAD
                PedidoEN pedidoEN = pedidoCEN.ReadOID (lineaPedidoEN.Pedido.Id);

                pedidoEN.Total -= restar;
                pedidoEN.Total += lineaPedidoEN.Precio * lineaPedidoEN.Cantidad;

                pedidoCAD.ModifyDefault (pedidoEN);

                lineaPedidoCAD.Modify (lineaPedidoEN);


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
