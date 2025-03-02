using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class PedidoViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int usuario { get; set; }


        [ScaffoldColumn(false)]
        [Display(Prompt = "Tarjeta: ", Description = "Tarjeta: ", Name = "Tarjeta ")]
        public int tarjeta { get; set; }


        [ScaffoldColumn(false)]
        [Display(Prompt = "Dirección: ", Description = "Dirección: ", Name = "Dirección ")]
        public int direccion { get; set; }





        [Display(Prompt = "Fecha: ", Description = "Fecha: ", Name = "Fecha ")]
        [DataType(DataType.DateTime, ErrorMessage = "Debe introducir una fecha")]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd/MM/yyyy}")]

        public DateTime Fecha { get; set; }






        [Display(Prompt = "Total: ", Description = "Total: ", Name = "Total")]
        [Range(minimum: 0, maximum: 1000000, ErrorMessage = "El total ha de ser mayor que 0 y menor que 1000000")]

        public double Total { get; set; }



        [Display(Prompt = "Cantidad: ", Description = "Cantidad: ", Name = "Cantidad")]
        //[Required(ErrorMessage = "Debes indicar una cantidad")]
        [Range(minimum: 0, maximum: 10000, ErrorMessage = "La cantidad ha de ser mayor que 0 y menor que 10000")]
        public int Cantidad { get; set; }



        [Display(Prompt = "Método de pago: ", Description = "Método de pago: ", Name = "Método de pago")]
        [Required(ErrorMessage = "Debes indicar un método de pago")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.PagoEnum MetodoPago { get; set; }



        [Display(Prompt = "Estado: ", Description = "Estado: ", Name = "Estado")]
        //[Required(ErrorMessage = "Debes indicar un estado")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.EstadoEnum Estado { get; set; }

    }
}