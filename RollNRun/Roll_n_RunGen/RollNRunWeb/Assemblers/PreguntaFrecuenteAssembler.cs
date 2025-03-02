using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace RollNRunWeb.Assemblers
{
    public class PreguntaFrecuenteAssembler
    {
        public PreguntaFrecuenteViewModel ConvertENToModelUI(PreguntaFrecuenteEN en)
        {
            PreguntaFrecuenteViewModel faq = new PreguntaFrecuenteViewModel();
            faq.id = en.Id;
            faq.pregunta = en.Pregunta;
            faq.respuesta = en.Respuesta;

            return faq;
        }

        public IList<PreguntaFrecuenteViewModel> ConvertListENToModel(IList<PreguntaFrecuenteEN> ens)
        {
            IList<PreguntaFrecuenteViewModel> faqs = new List<PreguntaFrecuenteViewModel>();
            foreach (PreguntaFrecuenteEN en in ens)
            {
                faqs.Add(ConvertENToModelUI(en));
            }

            return faqs;
        }
    }
}