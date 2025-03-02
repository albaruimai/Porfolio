
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



/*PROTECTED REGION ID(usingRoll_n_RunGenNHibernate.CP.Roll_n_Run_Factura_new_) ENABLED START*/
//  references to other libraries
/*PROTECTED REGION END*/

namespace Roll_n_RunGenNHibernate.CP.Roll_n_Run
{
public partial class FacturaCP : BasicCP
{
public Roll_n_RunGenNHibernate.EN.Roll_n_Run.FacturaEN New_ (Nullable<DateTime> p_fechaFacturacion, int p_pedido)
{
        /*PROTECTED REGION ID(Roll_n_RunGenNHibernate.CP.Roll_n_Run_Factura_new_) ENABLED START*/

        IFacturaCAD facturaCAD = null;
        FacturaCEN facturaCEN = null;
        PedidoCAD pedidoCAD = null;
        PedidoCEN pedidoCEN = null;


        Roll_n_RunGenNHibernate.EN.Roll_n_Run.FacturaEN result = null;


        try
        {
                SessionInitializeTransaction ();
                facturaCAD = new FacturaCAD (session);
                facturaCEN = new  FacturaCEN (facturaCAD);

                pedidoCAD = new PedidoCAD (session);
                pedidoCEN = new PedidoCEN (pedidoCAD);

                int oid;
                //Initialized FacturaEN
                FacturaEN facturaEN;
                facturaEN = new FacturaEN ();
                facturaEN.FechaFacturacion = p_fechaFacturacion;

                PedidoEN pedidoEN = pedidoCEN.ReadOID (p_pedido);


                if (p_pedido != -1) {
                        facturaEN.Pedido = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN ();
                        facturaEN.Pedido.Id = p_pedido;
                }

                facturaEN.Fecha = pedidoEN.Fecha;
                facturaEN.MetodoPago = pedidoEN.MetodoPago;
                facturaEN.Precio = pedidoEN.Total;

                //Call to FacturaCAD

                oid = facturaCAD.New_ (facturaEN);
                result = facturaCAD.ReadOIDDefault (oid);



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
