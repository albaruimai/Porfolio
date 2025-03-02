
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
 * Clase Devolucion:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class DevolucionCAD : BasicCAD, IDevolucionCAD
{
public DevolucionCAD() : base ()
{
}

public DevolucionCAD(ISession sessionAux) : base (sessionAux)
{
}



public DevolucionEN ReadOIDDefault (int id
                                    )
{
        DevolucionEN devolucionEN = null;

        try
        {
                SessionInitializeTransaction ();
                devolucionEN = (DevolucionEN)session.Get (typeof(DevolucionEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return devolucionEN;
}

public System.Collections.Generic.IList<DevolucionEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<DevolucionEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(DevolucionEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<DevolucionEN>();
                        else
                                result = session.CreateCriteria (typeof(DevolucionEN)).List<DevolucionEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (DevolucionEN devolucion)
{
        try
        {
                SessionInitializeTransaction ();
                DevolucionEN devolucionEN = (DevolucionEN)session.Load (typeof(DevolucionEN), devolucion.Id);

                devolucionEN.Descripcion = devolucion.Descripcion;


                devolucionEN.Motivo = devolucion.Motivo;



                session.Update (devolucionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (DevolucionEN devolucion)
{
        try
        {
                SessionInitializeTransaction ();
                if (devolucion.Pedido != null) {
                        // Argumento OID y no colección.
                        devolucion.Pedido = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.PedidoEN), devolucion.Pedido.Id);

                        devolucion.Pedido.Devolucion
                                = devolucion;
                }
                if (devolucion.Usuario != null) {
                        // Argumento OID y no colección.
                        devolucion.Usuario = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), devolucion.Usuario.Id);

                        devolucion.Usuario.Devolucion
                        .Add (devolucion);
                }

                session.Save (devolucion);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return devolucion.Id;
}

public void Modify (DevolucionEN devolucion)
{
        try
        {
                SessionInitializeTransaction ();
                DevolucionEN devolucionEN = (DevolucionEN)session.Load (typeof(DevolucionEN), devolucion.Id);

                devolucionEN.Descripcion = devolucion.Descripcion;


                devolucionEN.Motivo = devolucion.Motivo;

                session.Update (devolucionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
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
                DevolucionEN devolucionEN = (DevolucionEN)session.Load (typeof(DevolucionEN), id);
                session.Delete (devolucionEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: DevolucionEN
public DevolucionEN ReadOID (int id
                             )
{
        DevolucionEN devolucionEN = null;

        try
        {
                SessionInitializeTransaction ();
                devolucionEN = (DevolucionEN)session.Get (typeof(DevolucionEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return devolucionEN;
}

public System.Collections.Generic.IList<DevolucionEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<DevolucionEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(DevolucionEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<DevolucionEN>();
                else
                        result = session.CreateCriteria (typeof(DevolucionEN)).List<DevolucionEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in DevolucionCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
}
}
