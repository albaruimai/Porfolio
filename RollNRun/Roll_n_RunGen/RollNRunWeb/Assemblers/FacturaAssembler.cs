using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Assemblers
{
    public class FacturaAssembler
    {
        public FacturaViewModel ConvertENToModelUI(FacturaEN en)
        {
            FacturaViewModel fact = new FacturaViewModel();
            fact.id = en.Id;
            fact.fecha = (System.DateTime)en.Fecha;
            fact.fechaFacturacion = (System.DateTime)en.FechaFacturacion;
            fact.precio = en.Precio;
            fact.metodoPago = en.MetodoPago;

            return fact;
        }

        public IList<FacturaViewModel> ConvertListENToModel(IList<FacturaEN> ens)
        {
            IList<FacturaViewModel> facts = new List<FacturaViewModel>();
            foreach (FacturaEN en in ens)
            {
                facts.Add(ConvertENToModelUI(en));
            }
            return facts;
        }
    }
}