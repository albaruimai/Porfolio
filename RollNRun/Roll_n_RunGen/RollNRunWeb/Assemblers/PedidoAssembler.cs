using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;


namespace RollNRunWeb.Assemblers
{
    public class PedidoAssembler
    {
        public PedidoViewModel ConvertENToModelUI(PedidoEN P)
        {
            PedidoViewModel ped = new PedidoViewModel();
            ped.id = P.Id;
            ped.Fecha = (DateTime)P.Fecha;
            ped.Total = P.Total;
            ped.Cantidad = P.Cantidad;
            ped.MetodoPago = P.MetodoPago;
            ped.Estado = P.Estado;
            if (P.Tarjeta != null) {
                ped.tarjeta = P.Tarjeta.Id;
            }
            if (P.Direccion != null)
            {
                ped.direccion = P.Direccion.Id;
            }


            return ped;
        }

        public IList<PedidoViewModel> ConvertListENToModel(IList<PedidoEN> peds)
        {
            IList<PedidoViewModel> pediciones = new List<PedidoViewModel>();
            foreach (PedidoEN pedit in peds)
            {
                pediciones.Add(ConvertENToModelUI(pedit));
            }
            return pediciones;
        }

    }
}