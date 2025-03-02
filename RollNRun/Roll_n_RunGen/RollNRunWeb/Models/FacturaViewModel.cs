using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class FacturaViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int pedido { get; set; }

        [Display(Prompt = "Fecha ", Description = "Fecha ", Name = "Fecha ")]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd/MM/yyyy}")]
        public DateTime fecha { get; set; }

        [Display(Prompt = "Fecha de Facturación", Description = "Fecha de Facturación", Name = "Fecha de Facturación")]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd/MM/yyyy}")]
        public DateTime fechaFacturacion { get; set; }


        [Display(Prompt = "Total: ", Description = "Total: ", Name = "Total")]
        public double precio { get; set; }

        [Display(Prompt = "Método de pago: ", Description = "Método de pago: ", Name = "Método de pago")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum metodoPago { get; set; }
    }
}