using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Assemblers
{
    public class UsuarioAssembler
    {
        public UsuarioViewModel ConvertENToModelUI(UsuarioEN en)
        {
            UsuarioViewModel usu = new UsuarioViewModel();
            usu.id = en.Id;
            usu.alias = en.Nickname;
            usu.Password = en.Pass;
            usu.Email = en.Email;
            usu.nombre = en.Nombre;
            usu.apellidos = en.Apellidos;
            usu.telefono = en.Telefono;
            usu.rol = en.Rol;
            usu.imagen_perfil = en.Imagen;

            return usu;
        }

        public IList<UsuarioViewModel> ConvertListENToModel(IList<UsuarioEN> ens)
        {
            IList<UsuarioViewModel> usus = new List<UsuarioViewModel>();
            foreach (UsuarioEN en in ens)
            {
                usus.Add(ConvertENToModelUI(en));
            }

            return usus;
        }
    }
}