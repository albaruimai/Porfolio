using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;

namespace RollNRunWeb.Assemblers
{
    public class TarjetaAssembler
    {
        public TarjetaViewModel ConvertENToModelUI(TarjetaEN en)
        {
            TarjetaViewModel tar = new TarjetaViewModel();
            tar.id = en.Id;
            tar.titular = en.Titular;
            tar.numero = en.Numero;
            tar.cvv = en.Cvv;
            tar.fechaCad = (DateTime)en.FechaCad;
            tar.usuario = en.Usuario.Id;
            return tar;
        }

        public IList<TarjetaViewModel> ConvertListENToModel(IList<TarjetaEN> ens)
        {
            IList<TarjetaViewModel> tars = new List<TarjetaViewModel>();
            foreach (TarjetaEN en in ens)
            {
                tars.Add(ConvertENToModelUI(en));
            }
            return tars;
        }
    }
}