using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class PreguntaFrecuenteViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }

        [Display(Prompt = "Pregunta", Description = "Pregunta Frecuente creada", Name = "Pregunta")]
        [Required(ErrorMessage = "Debe indicar una pregunta para crear una FAQ")]
        public string pregunta { get; set; }

        [Display(Prompt = "Respuesta", Description = "Respuesta Frecuente creada", Name = "Respuesta")]
        [Required(ErrorMessage = "Debe indicar una respuesta para crear una FAQ")]
        public string respuesta { get; set; }
    }
}