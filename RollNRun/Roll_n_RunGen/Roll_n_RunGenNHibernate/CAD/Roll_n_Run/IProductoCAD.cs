
using System;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace Roll_n_RunGenNHibernate.CAD.Roll_n_Run
{
public partial interface IProductoCAD
{
ProductoEN ReadOIDDefault (int id
                           );

void ModifyDefault (ProductoEN producto);

System.Collections.Generic.IList<ProductoEN> ReadAllDefault (int first, int size);



int New_ (ProductoEN producto);

void Modify (ProductoEN producto);


void Destroy (int id
              );


ProductoEN ReadOID (int id
                    );


System.Collections.Generic.IList<ProductoEN> ReadAll (int first, int size);





System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarPrecio (double ? p_precio);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarNombre (string p_nombre);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarTipo (Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Tipo_productoEnum ? p_tipo);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> GetProductosDeseadosUsuario (int ? p_usuario);


void MarcarDeseado (int p_Producto_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs);


System.Collections.Generic.IList<Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN> BuscarOfertas ();


void QuitarDeseado (int p_Producto_OID, System.Collections.Generic.IList<int> p_usuarios_OIDs);
}
}
