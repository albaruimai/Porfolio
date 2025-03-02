
using System;
using System.Text;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using NHibernate;
using NHibernate.Cfg;
using NHibernate.Criterion;
using NHibernate.Exceptions;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.Exceptions;


/*
 * Clase PreguntaFrecuente:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class PreguntaFrecuenteCAD : BasicCAD, IPreguntaFrecuenteCAD
{
public PreguntaFrecuenteCAD() : base ()
{
}

public PreguntaFrecuenteCAD(ISession sessionAux) : base (sessionAux)
{
}



public PreguntaFrecuenteEN ReadOIDDefault (int id
                                           )
{
        PreguntaFrecuenteEN preguntaFrecuenteEN = null;

        try
        {
                SessionInitializeTransaction ();
                preguntaFrecuenteEN = (PreguntaFrecuenteEN)session.Get (typeof(PreguntaFrecuenteEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return preguntaFrecuenteEN;
}

public System.Collections.Generic.IList<PreguntaFrecuenteEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<PreguntaFrecuenteEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(PreguntaFrecuenteEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<PreguntaFrecuenteEN>();
                        else
                                result = session.CreateCriteria (typeof(PreguntaFrecuenteEN)).List<PreguntaFrecuenteEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (PreguntaFrecuenteEN preguntaFrecuente)
{
        try
        {
                SessionInitializeTransaction ();
                PreguntaFrecuenteEN preguntaFrecuenteEN = (PreguntaFrecuenteEN)session.Load (typeof(PreguntaFrecuenteEN), preguntaFrecuente.Id);

                preguntaFrecuenteEN.Pregunta = preguntaFrecuente.Pregunta;


                preguntaFrecuenteEN.Respuesta = preguntaFrecuente.Respuesta;

                session.Update (preguntaFrecuenteEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (PreguntaFrecuenteEN preguntaFrecuente)
{
        try
        {
                SessionInitializeTransaction ();

                session.Save (preguntaFrecuente);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return preguntaFrecuente.Id;
}

public void Modify (PreguntaFrecuenteEN preguntaFrecuente)
{
        try
        {
                SessionInitializeTransaction ();
                PreguntaFrecuenteEN preguntaFrecuenteEN = (PreguntaFrecuenteEN)session.Load (typeof(PreguntaFrecuenteEN), preguntaFrecuente.Id);

                preguntaFrecuenteEN.Pregunta = preguntaFrecuente.Pregunta;


                preguntaFrecuenteEN.Respuesta = preguntaFrecuente.Respuesta;

                session.Update (preguntaFrecuenteEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}
public void Destroy (int id
                     )
{
        try
        {
                SessionInitializeTransaction ();
                PreguntaFrecuenteEN preguntaFrecuenteEN = (PreguntaFrecuenteEN)session.Load (typeof(PreguntaFrecuenteEN), id);
                session.Delete (preguntaFrecuenteEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: PreguntaFrecuenteEN
public PreguntaFrecuenteEN ReadOID (int id
                                    )
{
        PreguntaFrecuenteEN preguntaFrecuenteEN = null;

        try
        {
                SessionInitializeTransaction ();
                preguntaFrecuenteEN = (PreguntaFrecuenteEN)session.Get (typeof(PreguntaFrecuenteEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return preguntaFrecuenteEN;
}

public System.Collections.Generic.IList<PreguntaFrecuenteEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<PreguntaFrecuenteEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(PreguntaFrecuenteEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<PreguntaFrecuenteEN>();
                else
                        result = session.CreateCriteria (typeof(PreguntaFrecuenteEN)).List<PreguntaFrecuenteEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in PreguntaFrecuenteCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
