
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
 * Clase Entrada:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class EntradaCAD : BasicCAD, IEntradaCAD
{
public EntradaCAD() : base ()
{
}

public EntradaCAD(ISession sessionAux) : base (sessionAux)
{
}



public EntradaEN ReadOIDDefault (int id
                                 )
{
        EntradaEN entradaEN = null;

        try
        {
                SessionInitializeTransaction ();
                entradaEN = (EntradaEN)session.Get (typeof(EntradaEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return entradaEN;
}

public System.Collections.Generic.IList<EntradaEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<EntradaEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(EntradaEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<EntradaEN>();
                        else
                                result = session.CreateCriteria (typeof(EntradaEN)).List<EntradaEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (EntradaEN entrada)
{
        try
        {
                SessionInitializeTransaction ();
                EntradaEN entradaEN = (EntradaEN)session.Load (typeof(EntradaEN), entrada.Id);



                entradaEN.Texto = entrada.Texto;


                session.Update (entradaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (EntradaEN entrada)
{
        try
        {
                SessionInitializeTransaction ();
                if (entrada.Subforo != null) {
                        // Argumento OID y no colección.
                        entrada.Subforo = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN), entrada.Subforo.Id);

                        entrada.Subforo.Entrada
                        .Add (entrada);
                }
                if (entrada.Usuario != null) {
                        // Argumento OID y no colección.
                        entrada.Usuario = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), entrada.Usuario.Id);

                        entrada.Usuario.Entrada
                        .Add (entrada);
                }

                session.Save (entrada);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return entrada.Id;
}

public void Modify (EntradaEN entrada)
{
        try
        {
                SessionInitializeTransaction ();
                EntradaEN entradaEN = (EntradaEN)session.Load (typeof(EntradaEN), entrada.Id);

                entradaEN.Texto = entrada.Texto;

                session.Update (entradaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
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
                EntradaEN entradaEN = (EntradaEN)session.Load (typeof(EntradaEN), id);
                session.Delete (entradaEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: EntradaEN
public EntradaEN ReadOID (int id
                          )
{
        EntradaEN entradaEN = null;

        try
        {
                SessionInitializeTransaction ();
                entradaEN = (EntradaEN)session.Get (typeof(EntradaEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return entradaEN;
}

public System.Collections.Generic.IList<EntradaEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<EntradaEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(EntradaEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<EntradaEN>();
                else
                        result = session.CreateCriteria (typeof(EntradaEN)).List<EntradaEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasSubforo (int ? p_subforo)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM EntradaEN self where select ent FROM EntradaEN as ent inner join ent.Subforo as subf where subf.Id = :p_subforo";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("EntradaENgetEntradasSubforoHQL");
                query.SetParameter ("p_subforo", p_subforo);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> GetEntradasUsuario (int p_usu)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM EntradaEN self where select ent FROM EntradaEN as ent inner join ent.Usuario as usu where usu.Id = :p_usu";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("EntradaENgetEntradasUsuarioHQL");
                query.SetParameter ("p_usu", p_usu);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.EntradaEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in EntradaCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
