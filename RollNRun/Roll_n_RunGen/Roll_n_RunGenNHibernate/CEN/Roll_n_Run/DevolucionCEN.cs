

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
 *      Definition of the class DevolucionCEN
 *
 */
public partial class DevolucionCEN
{
private IDevolucionCAD _IDevolucionCAD;

public DevolucionCEN()
{
        this._IDevolucionCAD = new DevolucionCAD ();
}

public DevolucionCEN(IDevolucionCAD _IDevolucionCAD)
{
        this._IDevolucionCAD = _IDevolucionCAD;
}

public IDevolucionCAD get_IDevolucionCAD ()
{
        return this._IDevolucionCAD;
}

public int New_ (string p_descripcion, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum p_motivo, int p_pedido, int p_usuario)
{
        DevolucionEN devolucionEN = null;
        int oid;

        //Initialized DevolucionEN
        devolucionEN = new DevolucionEN ();
        devolucionEN.Descripcion = p_descripcion;

        devolucionEN.Motivo = p_motivo;


        if (p_pedido != -1) {
                // El argumento p_pedido -> Property pedido es oid = false
                // Lista de oids id
                devolucionEN.Pedido = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN ();
                devolucionEN.Pedido.Id = p_pedido;
        }


        if (p_usuario != -1) {
                // El argumento p_usuario -> Property usuario es oid = false
                // Lista de oids id
                devolucionEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                devolucionEN.Usuario.Id = p_usuario;
        }

        //Call to DevolucionCAD

        oid = _IDevolucionCAD.New_ (devolucionEN);
        return oid;
}

public void Modify (int p_Devolucion_OID, string p_descripcion, Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum p_motivo)
{
        DevolucionEN devolucionEN = null;

        //Initialized DevolucionEN
        devolucionEN = new DevolucionEN ();
        devolucionEN.Id = p_Devolucion_OID;
        devolucionEN.Descripcion = p_descripcion;
        devolucionEN.Motivo = p_motivo;
        //Call to DevolucionCAD

        _IDevolucionCAD.Modify (devolucionEN);
}

public void Destroy (int id
                     )
{
        _IDevolucionCAD.Destroy (id);
}

public DevolucionEN ReadOID (int id
                             )
{
        DevolucionEN devolucionEN = null;

        devolucionEN = _IDevolucionCAD.ReadOID (id);
        return devolucionEN;
}

public System.Collections.Generic.IList<DevolucionEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<DevolucionEN> list = null;

        list = _IDevolucionCAD.ReadAll (first, size);
        return list;
}
}
}
