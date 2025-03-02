using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using RollNRunWeb.Assemblers;
using RollNRunWeb.Models;

namespace RollNRunWeb.Controllers
{
    [Authorize]
    public class TarjetaController : BasicController
    {
        // GET: Tarjeta
        public ActionResult Index()
        {
            SessionInitialize();
            TarjetaCAD tarCAD = new TarjetaCAD(session);
            TarjetaCEN tarCEN = new TarjetaCEN(tarCAD);
            IList<TarjetaEN> listEN = tarCEN.GetTarjetasUsuario(((UsuarioEN)Session["Usuario"]).Id);
            IEnumerable<TarjetaViewModel> listViewModel = new TarjetaAssembler().ConvertListENToModel(listEN).ToList();
            SessionClose();

            return View(listViewModel);
        }

        // GET: Tarjeta/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            TarjetaCAD tarjetaCAD = new TarjetaCAD(session);
            TarjetaCEN tarjetaCEN = new TarjetaCEN(tarjetaCAD);

            TarjetaEN tarjetaEN = tarjetaCEN.ReadOID(id);
            TarjetaViewModel tarjetaViewModel = new TarjetaAssembler().ConvertENToModelUI(tarjetaEN);

            SessionClose();

            return View(tarjetaViewModel);
        }

        // GET: Tarjeta/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Tarjeta/Create
        [HttpPost]
        public ActionResult Create(TarjetaViewModel tar)
        {
            try
            {
                TarjetaCEN tarCEN = new TarjetaCEN();
                if (Session["Usuario"] != null) {
                    tar.usuario = ((UsuarioEN)Session["Usuario"]).Id;
                }
                tarCEN.New_(tar.titular, tar.numero, tar.cvv, tar.fechaCad, tar.usuario);
                return RedirectToAction("Index");
                //Aqui falta que muestre algun error si pasa algo aunque deberia de tener siempre usuario porque sino no va a llegar aqui
            }
            catch
            {
                return View();
            }
        }

        // GET: Tarjeta/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            TarjetaCAD tarjetaCAD = new TarjetaCAD(session);
            TarjetaCEN tarjetaCEN = new TarjetaCEN(tarjetaCAD);

            TarjetaEN tarjetaEN = tarjetaCEN.ReadOID(id);
            TarjetaViewModel tarjetaViewModel = new TarjetaAssembler().ConvertENToModelUI(tarjetaEN);

            SessionClose();

            return View(tarjetaViewModel);
        }

        // POST: Tarjeta/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, TarjetaViewModel tarj)
        {
            try
            {

                TarjetaCEN tarjetaCEN = new TarjetaCEN();
                TarjetaEN tarjetaEN = tarjetaCEN.ReadOID(id);
                tarjetaCEN.Modify(id, tarj.titular, tarj.numero, tarj.cvv, tarj.fechaCad);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        // GET: Tarjeta/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            TarjetaCAD tarjetaCAD = new TarjetaCAD(session);
            TarjetaCEN tarjetaCEN = new TarjetaCEN(tarjetaCAD);

            TarjetaEN tarjetaEN = tarjetaCEN.ReadOID(id);
            TarjetaViewModel tarjetaViewModel = new TarjetaAssembler().ConvertENToModelUI(tarjetaEN);

            SessionClose();
            return View(tarjetaViewModel);
        }

        // POST: Tarjeta/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, TarjetaViewModel tarj)
        {
            try
            {
                TarjetaCEN tarjetaCEN = new TarjetaCEN();
                tarjetaCEN.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
    }
}
