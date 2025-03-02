using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class LineaPedidoAssembler
    {
        public LineaPedidoViewModel ConvertENToModelUI(LineaPedidoEN linpe)
        {
            LineaPedidoViewModel lp = new LineaPedidoViewModel();
            lp.id = linpe.Id;
            lp.pedidoId = linpe.Pedido.Id;
            lp.productoId = linpe.Producto.Id;
            lp.productoNombre = linpe.Producto.Nombre;
            //lp.Producto = linpe.Producto;
            lp.cantidad = linpe.Cantidad;
            lp.precio = linpe.Precio;



            return lp;
        }

        public IList<LineaPedidoViewModel> ConvertListENToModel(IList<LineaPedidoEN> linpes)
        {
            IList<LineaPedidoViewModel> lps = new List<LineaPedidoViewModel>();
            foreach (LineaPedidoEN lp in linpes)
            {
                lps.Add(ConvertENToModelUI(lp));
            }
            return lps;
        }
    }
}