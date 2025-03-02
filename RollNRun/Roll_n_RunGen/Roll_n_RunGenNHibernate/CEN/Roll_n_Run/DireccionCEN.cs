

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
 *      Definition of the class DireccionCEN
 *
 */
public partial class DireccionCEN
{
private IDireccionCAD _IDireccionCAD;

public DireccionCEN()
{
        this._IDireccionCAD = new DireccionCAD ();
}

public DireccionCEN(IDireccionCAD _IDireccionCAD)
{
        this._IDireccionCAD = _IDireccionCAD;
}

public IDireccionCAD get_IDireccionCAD ()
{
        return this._IDireccionCAD;
}

public int New_ (string p_provincia, string p_localidad, string p_cp, string p_calle, int p_usuario)
{
        DireccionEN direccionEN = null;
        int oid;

        //Initialized DireccionEN
        direccionEN = new DireccionEN ();
        direccionEN.Provincia = p_provincia;

        direccionEN.Localidad = p_localidad;

        direccionEN.Cp = p_cp;

        direccionEN.Calle = p_calle;


        if (p_usuario != -1) {
                // El argumento p_usuario -> Property usuario es oid = false
                // Lista de oids id
                direccionEN.Usuario = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                direccionEN.Usuario.Id = p_usuario;
        }

        //Call to DireccionCAD

        oid = _IDireccionCAD.New_ (direccionEN);
        return oid;
}

public void Modify (int p_Direccion_OID, string p_provincia, string p_localidad, string p_cp, string p_calle)
{
        DireccionEN direccionEN = null;

        //Initialized DireccionEN
        direccionEN = new DireccionEN ();
        direccionEN.Id = p_Direccion_OID;
        direccionEN.Provincia = p_provincia;
        direccionEN.Localidad = p_localidad;
        direccionEN.Cp = p_cp;
        direccionEN.Calle = p_calle;
        //Call to DireccionCAD

        _IDireccionCAD.Modify (direccionEN);
}

public void Destroy (int id
                     )
{
        _IDireccionCAD.Destroy (id);
}

public DireccionEN ReadOID (int id
                            )
{
        DireccionEN direccionEN = null;

        direccionEN = _IDireccionCAD.ReadOID (id);
        return direccionEN;
}

public System.Collections.Generic.IList<DireccionEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<DireccionEN> list = null;

        list = _IDireccionCAD.ReadAll (first, size);
        return list;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.DireccionEN> GetDireccionesUsuario (int ? p_usuario)
{
        return _IDireccionCAD.GetDireccionesUsuario (p_usuario);
}
}
}
