using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Models
{
    public class UsuarioViewModel : RegisterViewModel
    {
        [ScaffoldColumn(false)]
        public int id { get; set; }

        [Display(Prompt = "Alias", Description = "Apodo del usuario", Name = "Alias ")]
        [Required(ErrorMessage = "Debe indicar un alias para el usuario")]
        [StringLength(maximumLength: 20, ErrorMessage = "El alias no puede tener más de 20 caracteres")]
        public string alias { get; set; }

        [Display(Prompt = "Nombre del usuario", Description = "Nombre del usuario", Name = "Nombre ")]
        [Required(ErrorMessage = "Debe indicar el nombre del usuario")]
        public string nombre { get; set; }

        [Display(Prompt = "Apellidos del usuario", Description = "Apellidos del usuario", Name = "Apellidos")]
        [Required(ErrorMessage = "Debe indicar al menos un apellido para el usuario")]
        public string apellidos { get; set; }

        [Display(Prompt = "Tipo de Usuario", Description = "Rol del Usuario en la página", Name = "Rol")]
        [Required(ErrorMessage = "Debe indicar el rol de Usuario")]
        public Roll_n_RunGenNHibernate.Enumerated.Roll_n_Run.RolEnum rol { get; set; }

        [Display(Prompt = "Imagen de perfil del usuario", Description = "Imagen de perfil del usuario", Name = "Imagen")]
        [StringLength(maximumLength: 300, ErrorMessage = "Elija otra ruta de imagen con 300 caracteres máximo")]
        public string imagen_perfil { get; set; }

        [Display(Prompt = "Telefono del usuario", Description = "Telefono del usuario", Name = "Telefono ")]
        public string telefono { get; set; }


    }
}