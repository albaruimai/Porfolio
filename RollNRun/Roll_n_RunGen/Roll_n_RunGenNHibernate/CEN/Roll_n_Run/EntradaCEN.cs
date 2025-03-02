

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
 *      Definition of the class EntradaCEN
 *
 */
public partial class EntradaCEN
{
private IEntradaCAD _IEntradaCAD;

public EntradaCEN()
{
        this._IEntradaCAD = new EntradaCAD ();
}

public EntradaCEN(IEntradaCAD _IEntradaCAD)
{
        this._IEntradaCAD = _IEntradaCAD;
}

public IEntradaCAD get_IEntradaCAD ()
{
        return this._IEntradaCAD;
}

public void Modify (int p_Entrada_OID, string p_texto)
{
        EntradaEN entradaEN = null;

        //Initialized EntradaEN
        entradaEN = new EntradaEN ();
        entradaEN.Id = p_Entrada_OID;
        entradaEN.Texto = p_texto;
        //Call to EntradaCAD

        _IEntradaCAD.Modify (entradaEN);
}

public EntradaEN ReadOID (int id
                          )
{
        EntradaEN entradaEN = null;

        entradaEN = _IEntradaCAD.ReadOID (id);
        return entradaEN;
}

public System.Collections.Generic.IList<EntradaEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<EntradaEN> list = null;

        list = _IEntradaCAD.ReadAll (first, size);
        return list;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasSubforo (int ? p_subforo)
{
        return _IEntradaCAD.GetEntradasSubforo (p_subforo);
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasUsuario (int p_usu)
{
        return _IEntradaCAD.GetEntradasUsuario (p_usu);
}
}
}
