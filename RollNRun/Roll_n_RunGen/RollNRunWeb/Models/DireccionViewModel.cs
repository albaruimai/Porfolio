using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class DireccionViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int usuario { get; set; }

        [Display(Prompt = "Provincia: ", Description = "Provincia: ", Name = "Provincia")]
        [Required(ErrorMessage = "Debes indicar una provincia")]
        [StringLength(maximumLength: 15, ErrorMessage = "La provincia no puede tener más de 15 caracteres")]

        public string Provincia { get; set; }

        [Display(Prompt = "Localidad: ", Description = "Localidad: ", Name = "Localidad")]
        [Required(ErrorMessage = "Debes indicar una localidad")]
        [StringLength(maximumLength: 25, ErrorMessage = "La localidad no puede tener más de 25 caracteres")]

        public string Localidad { get; set; }

        [Display(Prompt = "Código Postal: ", Description = "Código Postal: ", Name = "Código Postal")]
        [Required(ErrorMessage = "Debes indicar un código postal")]
        [DataType(DataType.PostalCode, ErrorMessage = "El código debe ser un número de 5 cifras")]
        public string CP { get; set; }

        [Display(Prompt = "Calle: ", Description = "Calle: ", Name = "Calle")]
        [Required(ErrorMessage = "Debes indicar una calle")]
        [StringLength(maximumLength: 50, ErrorMessage = "La calle no puede tener más de 50 caracteres")]

        public string Calle { get; set; }

    }
}