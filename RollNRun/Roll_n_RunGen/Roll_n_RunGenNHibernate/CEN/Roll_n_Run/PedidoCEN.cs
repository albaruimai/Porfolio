

using System;
using System.Text;
using System.Collections.Generic;
using Newtonsoft.Json;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using Roll_n_RunGenNHibernate.Exceptions;

using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;


namespace Roll_n_RunGenNHibernate.CEN.Roll_n_Run
{
/*
 *      Definition of the class PedidoCEN
 *
 */
public partial class PedidoCEN
{
private IPedidoCAD _IPedidoCAD;

public PedidoCEN()
{
        this._IPedidoCAD = new PedidoCAD ();
}

public PedidoCEN(IPedidoCAD _IPedidoCAD)
{
        this._IPedidoCAD = _IPedidoCAD;
}

public IPedidoCAD get_IPedidoCAD ()
{
        return this._IPedidoCAD;
}

public void Modify (int p_Pedido_OID, Nullable<DateTime> p_fecha, double p_total, int p_cantidad, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum p_metodoPago, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum p_estado)
{
        PedidoEN pedidoEN = null;

        //Initialized PedidoEN
        pedidoEN = new PedidoEN ();
        pedidoEN.Id = p_Pedido_OID;
        pedidoEN.Fecha = p_fecha;
        pedidoEN.Total = p_total;
        pedidoEN.Cantidad = p_cantidad;
        pedidoEN.MetodoPago = p_metodoPago;
        pedidoEN.Estado = p_estado;
        //Call to PedidoCAD

        _IPedidoCAD.Modify (pedidoEN);
}

public void Destroy (int id
                     )
{
        _IPedidoCAD.Destroy (id);
}

public PedidoEN ReadOID (int id
                         )
{
        PedidoEN pedidoEN = null;

        pedidoEN = _IPedidoCAD.ReadOID (id);
        return pedidoEN;
}

public System.Collections.Generic.IList<PedidoEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<PedidoEN> list = null;

        list = _IPedidoCAD.ReadAll (first, size);
        return list;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> GetPedidosEstado (Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum ? p_estado)
{
        return _IPedidoCAD.GetPedidosEstado (p_estado);
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN> GetPedidosUsuario (int ? p_usuario)
{
        return _IPedidoCAD.GetPedidosUsuario (p_usuario);
}
}
}
