using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class ProductoViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int usuario { get; set; }
        [ScaffoldColumn(false)]
        public int lineaPedido { get; set; }
        [ScaffoldColumn(false)]
        public int entrada { get; set; }

        [Display(Prompt = "Nombre", Description = "Nombre del producto", Name = "Nombre del producto")]
        [Required(ErrorMessage = "Debe indicar un nombre para el producto")]
        [StringLength(maximumLength: 50, ErrorMessage = "El nombre debe tener como mucho 50 caracteres")]
        public string nombre { get; set; }

        [Display(Prompt = "Marca", Description = "Nombre de la marca", Name = "Marca")]
        [Required(ErrorMessage = "Debe indicar una marca para el producto")]
        [StringLength(maximumLength: 25, ErrorMessage = "El nombre debe tener como mucho 25 caracteres")]
        public string marca { get; set; }

        [Display(Prompt = "Stock del producto", Description = "Stock del producto", Name = "Stock")]
        [Range(minimum: 0, maximum: 10000, ErrorMessage = "El número del stock ha de ser mayor que 0 y menor que 10000")]
        public int stock { get; set; }

        [Display(Prompt = "Precio del producto", Description = "Precio del producto", Name = "Precio")]
        [Required(ErrorMessage = "Debe indicar el precio del producto")]
        [DataType(DataType.Currency, ErrorMessage = "El precio debe ser un valor numérico")]
        [Range(minimum: 0, maximum: 10000, ErrorMessage = "El precio debe ser un número mayor que 0 y menor que 10000")]
        public string precio { get; set; }

        [Display(Prompt = "Imagen del producto", Description = "Imagen del producto", Name = "Imagen")]
        public string imagen { get; set; }

        [Display(Prompt = "Descripcion", Description = "Descripcion del producto", Name = "Descripcion")]
        [Required(ErrorMessage = "Debe escribir una descripcion para el producto")]
        [StringLength(maximumLength: 300, ErrorMessage = "La descripcion debe tener como mucho 300 caracteres")]
        public string descripcion { get; set; }

        [Display(Prompt = "Valoracion media del producto", Description = "Valoracion media del producto, por defecto inicia a 0", Name = "Valoracion media")]
        public double valMedia { get; set; }

        [Display(Prompt = "Tipo de producto", Description = "Tipo de producto", Name = "Tipo")]
        [Required(ErrorMessage = "Debe indicar el tipo de producto")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Tipo_productoEnum tipo_producto { get; set; }

        [Display(Prompt = "Oferta al producto", Description = "Oferta al producto", Name = "Oferta")]
        [Required(ErrorMessage = "Debe indicar una oferta para el producto")]
        [Range(minimum: 0, maximum: 100, ErrorMessage = "La oferta debe ser entre 0 y 100")]
        public double oferta { get; set; }
    }
}