using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Assemblers
{
    public class ProductoAssembler
    {
        public ProductoViewModel ConvertENToModelUI(ProductoEN en)
        {
            ProductoViewModel prod = new ProductoViewModel();
            prod.id = en.Id;
            prod.nombre = en.Nombre;
            prod.marca = en.Marca;
            prod.stock = en.Stock;
            prod.precio = en.Precio.ToString().Replace(",", ".");
            prod.imagen = en.Imagen;
            prod.descripcion = en.Descripcion;
            prod.valMedia = en.Val_media;
            prod.tipo_producto = en.Tipo;
            prod.oferta = en.Oferta;

            return prod;
        }

        public IList<ProductoViewModel> ConvertListENToModel(IList<ProductoEN> ens)
        {
            IList<ProductoViewModel> prods = new List<ProductoViewModel>();
            foreach (ProductoEN en in ens)
            {
                prods.Add(ConvertENToModelUI(en));
            }

            return prods;
        }
    }
}