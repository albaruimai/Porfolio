

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
 *      Definition of the class PreguntaFrecuenteCEN
 *
 */
public partial class PreguntaFrecuenteCEN
{
private IPreguntaFrecuenteCAD _IPreguntaFrecuenteCAD;

public PreguntaFrecuenteCEN()
{
        this._IPreguntaFrecuenteCAD = new PreguntaFrecuenteCAD ();
}

public PreguntaFrecuenteCEN(IPreguntaFrecuenteCAD _IPreguntaFrecuenteCAD)
{
        this._IPreguntaFrecuenteCAD = _IPreguntaFrecuenteCAD;
}

public IPreguntaFrecuenteCAD get_IPreguntaFrecuenteCAD ()
{
        return this._IPreguntaFrecuenteCAD;
}

public int New_ (string p_pregunta, string p_respuesta)
{
        PreguntaFrecuenteEN preguntaFrecuenteEN = null;
        int oid;

        //Initialized PreguntaFrecuenteEN
        preguntaFrecuenteEN = new PreguntaFrecuenteEN ();
        preguntaFrecuenteEN.Pregunta = p_pregunta;

        preguntaFrecuenteEN.Respuesta = p_respuesta;

        //Call to PreguntaFrecuenteCAD

        oid = _IPreguntaFrecuenteCAD.New_ (preguntaFrecuenteEN);
        return oid;
}

public void Modify (int p_PreguntaFrecuente_OID, string p_pregunta, string p_respuesta)
{
        PreguntaFrecuenteEN preguntaFrecuenteEN = null;

        //Initialized PreguntaFrecuenteEN
        preguntaFrecuenteEN = new PreguntaFrecuenteEN ();
        preguntaFrecuenteEN.Id = p_PreguntaFrecuente_OID;
        preguntaFrecuenteEN.Pregunta = p_pregunta;
        preguntaFrecuenteEN.Respuesta = p_respuesta;
        //Call to PreguntaFrecuenteCAD

        _IPreguntaFrecuenteCAD.Modify (preguntaFrecuenteEN);
}

public void Destroy (int id
                     )
{
        _IPreguntaFrecuenteCAD.Destroy (id);
}

public PreguntaFrecuenteEN ReadOID (int id
                                    )
{
        PreguntaFrecuenteEN preguntaFrecuenteEN = null;

        preguntaFrecuenteEN = _IPreguntaFrecuenteCAD.ReadOID (id);
        return preguntaFrecuenteEN;
}

public System.Collections.Generic.IList<PreguntaFrecuenteEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<PreguntaFrecuenteEN> list = null;

        list = _IPreguntaFrecuenteCAD.ReadAll (first, size);
        return list;
}
}
}
