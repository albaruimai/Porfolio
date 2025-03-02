using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class DevolucionViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int pedido { get; set; }
        [ScaffoldColumn(false)]
        public int usuario { get; set; }

        [Display(Prompt = "Motivo: ", Description = "Motivo: ", Name = "Motivo de la devolución")]
        [Required(ErrorMessage = "Debes indicar un motivo")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.Motivo_DevolucionEnum Motivo { get; set; }

        [Display(Prompt = "Descipción: ", Description = "Descripción: ", Name = "Descripción del motivo")]
        [Required(ErrorMessage = "Debes indicar una descripción")]
        [StringLength(maximumLength: 500, ErrorMessage = "La descripción no puede tener más de 500 caracteres")]

        public string Descripcion { get; set; }
    }
}