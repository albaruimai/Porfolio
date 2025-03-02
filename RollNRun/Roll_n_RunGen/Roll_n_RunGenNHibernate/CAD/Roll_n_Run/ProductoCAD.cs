
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
 * Clase Producto:
 *
 */

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial class ProductoCAD : BasicCAD, IProductoCAD
{
public ProductoCAD() : base ()
{
}

public ProductoCAD(ISession sessionAux) : base (sessionAux)
{
}



public ProductoEN ReadOIDDefault (int id
                                  )
{
        ProductoEN productoEN = null;

        try
        {
                SessionInitializeTransaction ();
                productoEN = (ProductoEN)session.Get (typeof(ProductoEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return productoEN;
}

public System.Collections.Generic.IList<ProductoEN> ReadAllDefault (int first, int size)
{
        System.Collections.Generic.IList<ProductoEN> result = null;
        try
        {
                using (ITransaction tx = session.BeginTransaction ())
                {
                        if (size > 0)
                                result = session.CreateCriteria (typeof(ProductoEN)).
                                         SetFirstResult (first).SetMaxResults (size).List<ProductoEN>();
                        else
                                result = session.CreateCriteria (typeof(ProductoEN)).List<ProductoEN>();
                }
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }

        return result;
}

// Modify default (Update all attributes of the class)

public void ModifyDefault (ProductoEN producto)
{
        try
        {
                SessionInitializeTransaction ();
                ProductoEN productoEN = (ProductoEN)session.Load (typeof(ProductoEN), producto.Id);

                productoEN.Nombre = producto.Nombre;


                productoEN.Marca = producto.Marca;


                productoEN.Stock = producto.Stock;


                productoEN.Precio = producto.Precio;


                productoEN.Imagen = producto.Imagen;


                productoEN.Descripcion = producto.Descripcion;




                productoEN.Val_media = producto.Val_media;



                productoEN.Tipo = producto.Tipo;



                productoEN.Oferta = producto.Oferta;

                session.Update (productoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}


public int New_ (ProductoEN producto)
{
        try
        {
                SessionInitializeTransaction ();

                session.Save (producto);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return producto.Id;
}

public void Modify (ProductoEN producto)
{
        try
        {
                SessionInitializeTransaction ();
                ProductoEN productoEN = (ProductoEN)session.Load (typeof(ProductoEN), producto.Id);

                productoEN.Nombre = producto.Nombre;


                productoEN.Marca = producto.Marca;


                productoEN.Stock = producto.Stock;


                productoEN.Precio = producto.Precio;


                productoEN.Imagen = producto.Imagen;


                productoEN.Descripcion = producto.Descripcion;


                productoEN.Val_media = producto.Val_media;


                productoEN.Tipo = producto.Tipo;


                productoEN.Oferta = producto.Oferta;

                session.Update (productoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
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
                ProductoEN productoEN = (ProductoEN)session.Load (typeof(ProductoEN), id);
                session.Delete (productoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

//Sin e: ReadOID
//Con e: ProductoEN
public ProductoEN ReadOID (int id
                           )
{
        ProductoEN productoEN = null;

        try
        {
                SessionInitializeTransaction ();
                productoEN = (ProductoEN)session.Get (typeof(ProductoEN), id);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return productoEN;
}

public System.Collections.Generic.IList<ProductoEN> ReadAll (int first, int size)
{
        System.Collections.Generic.IList<ProductoEN> result = null;
        try
        {
                SessionInitializeTransaction ();
                if (size > 0)
                        result = session.CreateCriteria (typeof(ProductoEN)).
                                 SetFirstResult (first).SetMaxResults (size).List<ProductoEN>();
                else
                        result = session.CreateCriteria (typeof(ProductoEN)).List<ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarPrecio (double ? p_precio)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM ProductoEN self where select prod FROM ProductoEN as prod where prod.Precio <= :p_precio";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("ProductoENbuscarPrecioHQL");
                query.SetParameter ("p_precio", p_precio);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarNombre (string p_nombre)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM ProductoEN self where select prod FROM ProductoEN as prod where prod.Nombre like '%' + :p_nombre + '%'  or prod.Descripcion like '%' + :p_nombre + '%' ";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("ProductoENbuscarNombreHQL");
                query.SetParameter ("p_nombre", p_nombre);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarTipo (Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Tipo_productoEnum ? p_tipo)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM ProductoEN self where select prod FROM ProductoEN as prod where prod.Tipo = :p_tipo";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("ProductoENbuscarTipoHQL");
                query.SetParameter ("p_tipo", p_tipo);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> GetProductosDeseadosUsuario (int ? p_usuario)
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM ProductoEN self where select prod FROM ProductoEN as prod inner join prod.Usuarios as usu where usu.Id = :p_usuario";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("ProductoENgetProductosDeseadosUsuarioHQL");
                query.SetParameter ("p_usuario", p_usuario);

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public void MarcarDeseado (int p_Producto_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs)
{
        Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN productoEN = null;
        try
        {
                SessionInitializeTransaction ();
                productoEN = (ProductoEN)session.Load (typeof(ProductoEN), p_Producto_OID);
                Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuariosENAux = null;
                if (productoEN.Usuarios == null) {
                        productoEN.Usuarios = new System.Collections.Generic.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN>();
                }

                foreach (int item in p_usuarios_OIDs) {
                        usuariosENAux = new Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN ();
                        usuariosENAux = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), item);
                        usuariosENAux.Productos_deseados.Add (productoEN);

                        productoEN.Usuarios.Add (usuariosENAux);
                }


                session.Update (productoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}

public System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarOfertas ()
{
        System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> result;
        try
        {
                SessionInitializeTransaction ();
                //String sql = @"FROM ProductoEN self where select prod FROM ProductoEN as prod where prod.Oferta > 0";
                //IQuery query = session.CreateQuery(sql);
                IQuery query = (IQuery)session.GetNamedQuery ("ProductoENbuscarOfertasHQL");

                result = query.List<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN>();
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }

        return result;
}
public void QuitarDeseado (int p_Producto_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs)
{
        try
        {
                SessionInitializeTransaction ();
                Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN productoEN = null;
                productoEN = (ProductoEN)session.Load (typeof(ProductoEN), p_Producto_OID);

                Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN usuariosENAux = null;
                if (productoEN.Usuarios != null) {
                        foreach (int item in p_usuarios_OIDs) {
                                usuariosENAux = (Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN)session.Load (typeof(Roll_n_RunGenNHibernate.EN.Roll_n_Run.UsuarioEN), item);
                                if (productoEN.Usuarios.Contains (usuariosENAux) == true) {
                                        productoEN.Usuarios.Remove (usuariosENAux);
                                        usuariosENAux.Productos_deseados.Remove (productoEN);
                                }
                                else
                                        throw new ModelException ("The identifier " + item + " in p_usuarios_OIDs you are trying to unrelationer, doesn't exist in ProductoEN");
                        }
                }

                session.Update (productoEN);
                SessionCommit ();
        }

        catch (Exception ex) {
                SessionRollBack ();
                if (ex is Roll_n_RunGenNHibernate.Exceptions.ModelException)
                        throw ex;
                throw new Roll_n_RunGenNHibernate.Exceptions.DataLayerException ("Error in ProductoCAD.", ex);
        }


        finally
        {
                SessionClose ();
        }
}
}
}
