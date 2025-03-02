using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class LineaPedidoViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }


        [Display(Prompt = "Id del Pedido: ", Description = "Id del Pedido: ", Name = "Id Pedido")]
        [Required(ErrorMessage = "Debes indicar un pedido")]
        public int pedidoId { get; set; }

        [Display(Prompt = "Id del producto: ", Description = "Id del Producto: ", Name = "Id Producto")]
        [Required(ErrorMessage = "Debes indicar un producto")]
        public int productoId { get; set; }

        [Display(Prompt = "Nombre del producto: ", Description = "Nombre del Producto: ", Name = "Nombre Producto")]
        [Required(ErrorMessage = "Debes indicar un nombre")]
        public string productoNombre { get; set; }

        [Display(Prompt = "Cantidad: ", Description = "Cantidad: ", Name = "Cantidad")]
        [Required(ErrorMessage = "Debes indicar una cantidad")]
        [Range(minimum: 0, maximum: 10000, ErrorMessage = "La cantidad ha de ser mayor que 0 y menor que 10000")]
        public int cantidad { get; set; }

        [Display(Prompt = "Precio: ", Description = "Precio: ", Name = "Precio")]
        [Required(ErrorMessage = "Debes indicar un precio")]
        [Range(minimum: 0, maximum: 10000, ErrorMessage = "El precio ha de ser mayor que 0 y menor que 10000")]
        public double precio { get; set; }

        /*
        [ScaffoldColumn(false)]
        [Display(Prompt = "Producto", Description = "Producto:", Name = "Producto")]
        [Required(ErrorMessage = "Debes indicar un producto")]
        public Roll_n_RunGenNHibernate.EN.Roll_n_Run.ProductoEN Producto { get; set; }

        */
    }
}