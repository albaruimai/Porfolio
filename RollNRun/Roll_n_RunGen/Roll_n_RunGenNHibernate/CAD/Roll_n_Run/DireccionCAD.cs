
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
 * Clase Direccion:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class DireccionCAD : BasicCAD, IDireccionCAD
{
public DireccionCAD() : base ()
{
}

public DireccionCAD(ISession sessionAux) : base (sessionAux)
{
}



public DireccionEN ReadOIDDefault (int id
                                   )
{
        DireccionEN direccionEN = null;

        try
        {
                SessionInitializeTransaction ();
                direccionEN = (DireccionEN)session.Get (typeof(DireccionEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return direccionEN;
}

public System.Collections.Generic.IList<DireccionEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<DireccionEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(DireccionEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<DireccionEN>();
                        else
                                result = session.CreateCriteria (typeof(DireccionEN)).List<DireccionEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (DireccionEN direccion)
{
        try
        {
                SessionInitializeTransaction ();
                DireccionEN direccionEN = (DireccionEN)session.Load (typeof(DireccionEN), direccion.Id);

                direccionEN.Provincia = direccion.Provincia;


                direccionEN.Localidad = direccion.Localidad;


                direccionEN.Cp = direccion.Cp;


                direccionEN.Calle = direccion.Calle;



                session.Update (direccionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (DireccionEN direccion)
{
        try
        {
                SessionInitializeTransaction ();
                if (direccion.Usuario != null) {
                        // Argumento OID y no colección.
                        direccion.Usuario = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), direccion.Usuario.Id);

                        direccion.Usuario.Direccion
                        .Add (direccion);
                }

                session.Save (direccion);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return direccion.Id;
}

public void Modify (DireccionEN direccion)
{
        try
        {
                SessionInitializeTransaction ();
                DireccionEN direccionEN = (DireccionEN)session.Load (typeof(DireccionEN), direccion.Id);

                direccionEN.Provincia = direccion.Provincia;


                direccionEN.Localidad = direccion.Localidad;


                direccionEN.Cp = direccion.Cp;


                direccionEN.Calle = direccion.Calle;

                session.Update (direccionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
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
                DireccionEN direccionEN = (DireccionEN)session.Load (typeof(DireccionEN), id);
                session.Delete (direccionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: DireccionEN
public DireccionEN ReadOID (int id
                            )
{
        DireccionEN direccionEN = null;

        try
        {
                SessionInitializeTransaction ();
                direccionEN = (DireccionEN)session.Get (typeof(DireccionEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return direccionEN;
}

public System.Collections.Generic.IList<DireccionEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<DireccionEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(DireccionEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<DireccionEN>();
                else
                        result = session.CreateCriteria (typeof(DireccionEN)).List<DireccionEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.DireccionEN> GetDireccionesUsuario (int ? p_usuario)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.DireccionEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM DireccionEN self where select dir FROM DireccionEN as dir inner join dir.Usuario as usu where usu.Id = :p_usuario";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("DireccionENgetDireccionesUsuarioHQL");
                query.SetParameter ("p_usuario", p_usuario);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.DireccionEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DireccionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
