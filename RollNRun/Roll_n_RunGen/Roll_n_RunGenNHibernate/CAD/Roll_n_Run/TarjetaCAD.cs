
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
 * Clase Tarjeta:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class TarjetaCAD : BasicCAD, ITarjetaCAD
{
public TarjetaCAD() : base ()
{
}

public TarjetaCAD(ISession sessionAux) : base (sessionAux)
{
}



public TarjetaEN ReadOIDDefault (int id
                                 )
{
        TarjetaEN tarjetaEN = null;

        try
        {
                SessionInitializeTransaction ();
                tarjetaEN = (TarjetaEN)session.Get (typeof(TarjetaEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return tarjetaEN;
}

public System.Collections.Generic.IList<TarjetaEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<TarjetaEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(TarjetaEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<TarjetaEN>();
                        else
                                result = session.CreateCriteria (typeof(TarjetaEN)).List<TarjetaEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (TarjetaEN tarjeta)
{
        try
        {
                SessionInitializeTransaction ();
                TarjetaEN tarjetaEN = (TarjetaEN)session.Load (typeof(TarjetaEN), tarjeta.Id);

                tarjetaEN.Titular = tarjeta.Titular;


                tarjetaEN.Numero = tarjeta.Numero;


                tarjetaEN.Cvv = tarjeta.Cvv;


                tarjetaEN.FechaCad = tarjeta.FechaCad;



                session.Update (tarjetaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (TarjetaEN tarjeta)
{
        try
        {
                SessionInitializeTransaction ();
                if (tarjeta.Usuario != null) {
                        // Argumento OID y no colección.
                        tarjeta.Usuario = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), tarjeta.Usuario.Id);

                        tarjeta.Usuario.Tarjeta
                        .Add (tarjeta);
                }

                session.Save (tarjeta);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return tarjeta.Id;
}

public void Modify (TarjetaEN tarjeta)
{
        try
        {
                SessionInitializeTransaction ();
                TarjetaEN tarjetaEN = (TarjetaEN)session.Load (typeof(TarjetaEN), tarjeta.Id);

                tarjetaEN.Titular = tarjeta.Titular;


                tarjetaEN.Numero = tarjeta.Numero;


                tarjetaEN.Cvv = tarjeta.Cvv;


                tarjetaEN.FechaCad = tarjeta.FechaCad;

                session.Update (tarjetaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
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
                TarjetaEN tarjetaEN = (TarjetaEN)session.Load (typeof(TarjetaEN), id);
                session.Delete (tarjetaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: TarjetaEN
public TarjetaEN ReadOID (int id
                          )
{
        TarjetaEN tarjetaEN = null;

        try
        {
                SessionInitializeTransaction ();
                tarjetaEN = (TarjetaEN)session.Get (typeof(TarjetaEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return tarjetaEN;
}

public System.Collections.Generic.IList<TarjetaEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<TarjetaEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(TarjetaEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<TarjetaEN>();
                else
                        result = session.CreateCriteria (typeof(TarjetaEN)).List<TarjetaEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.TarjetaEN> GetTarjetasUsuario (int ? p_usuario)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.TarjetaEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM TarjetaEN self where select tarj FROM TarjetaEN as tarj inner join tarj.Usuario as usu where usu.Id = :p_usuario";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("TarjetaENgetTarjetasUsuarioHQL");
                query.SetParameter ("p_usuario", p_usuario);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.TarjetaEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in TarjetaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
