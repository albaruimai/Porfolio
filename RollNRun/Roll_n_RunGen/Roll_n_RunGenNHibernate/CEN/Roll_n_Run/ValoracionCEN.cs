

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
 *      Definition of the class ValoracionCEN
 *
 */
public partial class ValoracionCEN
{
private IValoracionCAD _IValoracionCAD;

public ValoracionCEN()
{
        this._IValoracionCAD = new ValoracionCAD ();
}

public ValoracionCEN(IValoracionCAD _IValoracionCAD)
{
        this._IValoracionCAD = _IValoracionCAD;
}

public IValoracionCAD get_IValoracionCAD ()
{
        return this._IValoracionCAD;
}

public ValoracionEN ReadOID (int id
                             )
{
        ValoracionEN valoracionEN = null;

        valoracionEN = _IValoracionCAD.ReadOID (id);
        return valoracionEN;
}

public System.Collections.Generic.IList<ValoracionEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<ValoracionEN> list = null;

        list = _IValoracionCAD.ReadAll (first, size);
        return list;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN> GetValoracionesProducto (int ? p_producto)
{
        return _IValoracionCAD.GetValoracionesProducto (p_producto);
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ValoracionEN> GetValoracionesUsuario (int ? p_usuario)
{
        return _IValoracionCAD.GetValoracionesUsuario (p_usuario);
}
}
}
