using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class ValoracionViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }

        [ScaffoldColumn(false)]
        public int usuario { get; set; }

        [ScaffoldColumn(false)]
        public int producto { get; set; }

        [Display(Prompt = "Valoración del producto", Description = "Valoración del producto", Name = "Valor")]
        [Required(ErrorMessage = "Este es un campo requerido")]
        [Range(minimum:1, maximum: 5 , ErrorMessage = "Debe introducir un valor de 0 y 5")]
        public int valor { get; set; }

        [Display(Prompt = "Comentario sobre el producto", Description = "Comentario sobre el producto", Name = "Comentario")]
        [Required(ErrorMessage = "Este es un campo requerido")]
        [StringLength(maximumLength: 300, ErrorMessage = "El comentario debe tener como mucho 300 caracteres")]
        public string comentario { get; set; }


    }
}