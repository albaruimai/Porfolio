using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;

namespace RollNRunWeb.Models
{
    public class SubforoViewModel
    {

        [ScaffoldColumn(false)]
        public int id { get; set; }
        [ScaffoldColumn(false)]
        public IList<UsuarioEN> usuario { get; set; }
        [ScaffoldColumn(false)]
        public IList<int> entrada { get; set; }

        [Display(Prompt = "NumSeguidores: ", Description = "NumSeguidores: ", Name = "Número de seguidores")]
        [Required(ErrorMessage = "Debes india un numSeguidores")]

        public int Seguidores { get; set; }

        [Display(Prompt = "Autor: ", Description = "Autor: ", Name = "Autor del subforo")]
        [Required(ErrorMessage = "Debes indicar un autor")]

        public string Autor { get; set; }

        [Display(Prompt = "Título: ", Description = "Título: ", Name = "Título del subforo")]
        [Required(ErrorMessage = "Debes indicar un título")]
        [StringLength(maximumLength: 50, ErrorMessage = "El título no puede tener más de 50 caracteres")]

        public string Titulo { get; set; }

        [Display(Prompt = "Fecha: ", Description = "Fecha: ", Name = "Fecha del subforo")]
        [DataType(DataType.DateTime, ErrorMessage = "Debe introducir una fecha")]
        [DisplayFormat(ApplyFormatInEditMode = true, DataFormatString = "{0:dd/MM/yyyy}")]

        public DateTime Fecha { get; set; }

        [Display(Prompt = "Descripción: ", Description = "Descripción: ", Name = "Descripción del subforo")]
        [Required(ErrorMessage = "Debes indicar una descripción")]
        [StringLength(maximumLength: 200, ErrorMessage = "La descripción no puede tener más de 200 caracteres")]
        public string Descripcion { get; set; }

        [Display(Prompt = "NumEntradas: ", Description = "NumEntradas: ", Name = "NumEntradas del subforo")]

        public int NumEntradas { get; set; }

    }
}