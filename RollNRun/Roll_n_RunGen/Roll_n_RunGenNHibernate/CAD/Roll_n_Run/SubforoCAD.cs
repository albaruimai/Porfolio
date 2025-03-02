
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
 * Clase Subforo:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class SubforoCAD : BasicCAD, ISubforoCAD
{
public SubforoCAD() : base ()
{
}

public SubforoCAD(ISession sessionAux) : base (sessionAux)
{
}



public SubforoEN ReadOIDDefault (int id
                                 )
{
        SubforoEN subforoEN = null;

        try
        {
                SessionInitializeTransaction ();
                subforoEN = (SubforoEN)session.Get (typeof(SubforoEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return subforoEN;
}

public System.Collections.Generic.IList<SubforoEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<SubforoEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(SubforoEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<SubforoEN>();
                        else
                                result = session.CreateCriteria (typeof(SubforoEN)).List<SubforoEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (SubforoEN subforo)
{
        try
        {
                SessionInitializeTransaction ();
                SubforoEN subforoEN = (SubforoEN)session.Load (typeof(SubforoEN), subforo.Id);


                subforoEN.Titulo = subforo.Titulo;


                subforoEN.Fecha = subforo.Fecha;


                subforoEN.Descripcion = subforo.Descripcion;



                subforoEN.NumEntradas = subforo.NumEntradas;


                session.Update (subforoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (SubforoEN subforo)
{
        try
        {
                SessionInitializeTransaction ();
                if (subforo.Autor != null) {
                        // Argumento OID y no colección.
                        subforo.Autor = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), subforo.Autor.Id);

                        subforo.Autor.Subforo_autor
                        .Add (subforo);
                }

                session.Save (subforo);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return subforo.Id;
}

public void Modify (SubforoEN subforo)
{
        try
        {
                SessionInitializeTransaction ();
                SubforoEN subforoEN = (SubforoEN)session.Load (typeof(SubforoEN), subforo.Id);

                subforoEN.Titulo = subforo.Titulo;


                subforoEN.Fecha = subforo.Fecha;


                subforoEN.Descripcion = subforo.Descripcion;


                subforoEN.NumEntradas = subforo.NumEntradas;

                session.Update (subforoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
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
                SubforoEN subforoEN = (SubforoEN)session.Load (typeof(SubforoEN), id);
                session.Delete (subforoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: SubforoEN
public SubforoEN ReadOID (int id
                          )
{
        SubforoEN subforoEN = null;

        try
        {
                SessionInitializeTransaction ();
                subforoEN = (SubforoEN)session.Get (typeof(SubforoEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return subforoEN;
}

public System.Collections.Generic.IList<SubforoEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<SubforoEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(SubforoEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<SubforoEN>();
                else
                        result = session.CreateCriteria (typeof(SubforoEN)).List<SubforoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}

public void SeguirSubforo (int p_Subforo_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs)
{
        Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN subforoEN = null;
        try
        {
                SessionInitializeTransaction ();
                subforoEN = (SubforoEN)session.Load (typeof(SubforoEN), p_Subforo_OID);
                Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuariosENAux = null;
                if (subforoEN.Usuarios == null) {
                        subforoEN.Usuarios = new System.Collections.Generic.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN>();
                }

                foreach (int item in p_usuarios_OIDs) {
                        usuariosENAux = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                        usuariosENAux = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), item);
                        usuariosENAux.Subforos.Add (subforoEN);

                        subforoEN.Usuarios.Add (usuariosENAux);
                }


                session.Update (subforoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> GetSubforosUsuario (int p_autor)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM SubforoEN self where select sfor FROM SubforoEN as sfor inner join sfor.Autor as usu where usu.Id = :p_autor";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("SubforoENgetSubforosUsuarioHQL");
                query.SetParameter ("p_autor", p_autor);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> GetSeguidosUsuario (int p_usuarios)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM SubforoEN self where select sfor FROM SubforoEN as sfor inner join sfor.Usuarios as usu where usu.Id = :p_usuarios";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("SubforoENgetSeguidosUsuarioHQL");
                query.SetParameter ("p_usuarios", p_usuarios);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public void DejarSeguirSubforo (int p_Subforo_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs)
{
        try
        {
                SessionInitializeTransaction ();
                Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN subforoEN = null;
                subforoEN = (SubforoEN)session.Load (typeof(SubforoEN), p_Subforo_OID);

                Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuariosENAux = null;
                if (subforoEN.Usuarios != null) {
                        foreach (int item in p_usuarios_OIDs) {
                                usuariosENAux = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), item);
                                if (subforoEN.Usuarios.Contains (usuariosENAux) == true) {
                                        subforoEN.Usuarios.Remove (usuariosENAux);
                                        usuariosENAux.Subforos.Remove (subforoEN);
                                }
                                else
                                        throw new ModelException ("The identifier " + item + " in p_usuarios_OIDs you are trying to unrelationer, doesn't exist in SubforoEN");
                        }
                }

                session.Update (subforoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> BuscarTitulo (string p_titulo)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM SubforoEN self where select sfor FROM SubforoEN as sfor where sfor.Titulo like '%' + :p_titulo + '%' ";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("SubforoENbuscarTituloHQL");
                query.SetParameter ("p_titulo", p_titulo);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.SubforoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> GetUsuariosSubforo (int p_id)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM SubforoEN self where select usu FROM UsuarioEN as usu inner join usu.Subforos as sfor where sfor.Id = :p_id";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("SubforoENgetUsuariosSubforoHQL");
                query.SetParameter ("p_id", p_id);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in SubforoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
