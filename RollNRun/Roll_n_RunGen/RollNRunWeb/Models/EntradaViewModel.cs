using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class EntradaViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public int idSubforo { get; set; }
        [ScaffoldColumn(false)]
        public int idUsuario { get; set; }

        [Display(Prompt = "Subforo: ", Description = "Subforo: ", Name = "Subforo de la entrada")]
        [Required(ErrorMessage = "Debes indicar un subforo")]

        public string Subforo { get; set; }

        [Display(Prompt = "Usuario: ", Description = "Usuario: ", Name = "Usuario autor de la entrada")]
        [Required(ErrorMessage = "Debes indicar un usuario")]

        public string Usuario { get; set; }

        [Display(Prompt = "Texto: ", Description = "Texto: ", Name = "Texto de la entrada")]
        [Required(ErrorMessage = "Debes escribir algo")]
        [StringLength(maximumLength: 500, ErrorMessage = "El texto no puede tener más de 500 caracteres")]
        public string Texto { get; set; }

    }
}