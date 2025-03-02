

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
 *      Definition of the class TarjetaCEN
 *
 */
public partial class TarjetaCEN
{
private ITarjetaCAD _ITarjetaCAD;

public TarjetaCEN()
{
        this._ITarjetaCAD = new TarjetaCAD ();
}

public TarjetaCEN(ITarjetaCAD _ITarjetaCAD)
{
        this._ITarjetaCAD = _ITarjetaCAD;
}

public ITarjetaCAD get_ITarjetaCAD ()
{
        return this._ITarjetaCAD;
}

public int New_ (string p_titular, string p_numero, string p_cvv, Nullable<DateTime> p_fechaCad, int p_usuario)
{
        TarjetaEN tarjetaEN = null;
        int oid;

        //Initialized TarjetaEN
        tarjetaEN = new TarjetaEN ();
        tarjetaEN.Titular = p_titular;

        tarjetaEN.Numero = p_numero;

        tarjetaEN.Cvv = p_cvv;

        tarjetaEN.FechaCad = p_fechaCad;


        if (p_usuario != -1) {
                // El argumento p_usuario -> Property usuario es oid = false
                // Lista de oids id
                tarjetaEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                tarjetaEN.Usuario.Id = p_usuario;
        }

        //Call to TarjetaCAD

        oid = _ITarjetaCAD.New_ (tarjetaEN);
        return oid;
}

public void Modify (int p_Tarjeta_OID, string p_titular, string p_numero, string p_cvv, Nullable<DateTime> p_fechaCad)
{
        TarjetaEN tarjetaEN = null;

        //Initialized TarjetaEN
        tarjetaEN = new TarjetaEN ();
        tarjetaEN.Id = p_Tarjeta_OID;
        tarjetaEN.Titular = p_titular;
        tarjetaEN.Numero = p_numero;
        tarjetaEN.Cvv = p_cvv;
        tarjetaEN.FechaCad = p_fechaCad;
        //Call to TarjetaCAD

        _ITarjetaCAD.Modify (tarjetaEN);
}

public void Destroy (int id
                     )
{
        _ITarjetaCAD.Destroy (id);
}

public TarjetaEN ReadOID (int id
                          )
{
        TarjetaEN tarjetaEN = null;

        tarjetaEN = _ITarjetaCAD.ReadOID (id);
        return tarjetaEN;
}

public System.Collections.Generic.IList<TarjetaEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<TarjetaEN> list = null;

        list = _ITarjetaCAD.ReadAll (first, size);
        return list;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.TarjetaEN> GetTarjetasUsuario (int ? p_usuario)
{
        return _ITarjetaCAD.GetTarjetasUsuario (p_usuario);
}
}
}
