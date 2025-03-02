using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;
using Roll_n_RunGenNHibernate.EN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CEN.Roll_n_Run;
using Roll_n_RunGenNHibernate.CAD.Roll_n_Run;
using Roll_n_RunGenNHibernate.CP.Roll_n_Run;
using RollNRunWeb.Models;
using RollNRunWeb.Assemblers;

namespace RollNRunWeb.Controllers
{
    public class EntradaController : BasicController
    {
        // GET: Entrada
        public ActionResult Index()
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            IList<EntradaEN> entradasEN = entradaCEN.ReadAll(0, -1);
            IEnumerable<EntradaViewModel> entradasViewModel = new EntradaAssembler().ConvertListENToModel(entradasEN).ToList();
            SessionClose();

            return View(entradasViewModel);
        }

        // GET: Entrada/Details/5
        public ActionResult Details(int id)
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            EntradaEN entradaEN = entradaCEN.ReadOID(id);
            EntradaViewModel entradaViewModel = new EntradaAssembler().ConvertENToModelUI(entradaEN);
            SessionClose();

            return View(entradaViewModel);
        }
        [Authorize]
        // GET: Entrada/Create
        public ActionResult Create()
        {
            return View();
        }

        // POST: Entrada/Create
        [HttpPost]
        public ActionResult Create(EntradaViewModel entrada)
        {
            try
            {
                // TODO: Add insert logic here
                EntradaCP entradaCP = new EntradaCP();
                if (Session["Usuario"] != null)
                {
                    entrada.Usuario = ((UsuarioEN)Session["Usuario"]).Nickname;
                    entrada.idUsuario = ((UsuarioEN)Session["Usuario"]).Id;
                    entradaCP.New_(entrada.idSubforo, entrada.idUsuario, entrada.Texto);
                }

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Entrada/Edit/5
        public ActionResult Edit(int id)
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            EntradaEN entradaEN = entradaCEN.ReadOID(id);
            EntradaViewModel entradaViewModel = new EntradaAssembler().ConvertENToModelUI(entradaEN);

            SessionClose();

            return View(entradaViewModel);
        }

        // POST: Entrada/Edit/5
        [HttpPost]
        public ActionResult Edit(int id, EntradaViewModel entrada)
        {
            try
            {
                // TODO: Add update logic here
                EntradaCEN entradaCEN = new EntradaCEN();
                EntradaEN entradaEN = entradaCEN.ReadOID(id);
                entradaCEN.Modify(id, entrada.Texto);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }
        [Authorize]
        // GET: Entrada/Delete/5
        public ActionResult Delete(int id)
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            EntradaEN entradaEN = entradaCEN.ReadOID(id);
            EntradaViewModel entradaViewModel = new EntradaAssembler().ConvertENToModelUI(entradaEN);
            SessionClose();

            return View(entradaViewModel);
        }

        // POST: Entrada/Delete/5
        [HttpPost]
        public ActionResult Delete(int id, EntradaViewModel collection)
        {
            try
            {
                // TODO: Add delete logic here
                EntradaCP entradaCP = new EntradaCP();
                entradaCP.Destroy(id);

                return RedirectToAction("Index");
            }
            catch
            {
                return View();
            }
        }

        public ActionResult Entradas()
        {
            SessionInitialize();
            EntradaCAD entradaCAD = new EntradaCAD(session);
            EntradaCEN entradaCEN = new EntradaCEN(entradaCAD);

            IList<EntradaEN> entradasEN = entradaCEN.GetEntradasUsuario((int)Session["Usu_id"]);
            IEnumerable<EntradaViewModel> entradasViewModel = new EntradaAssembler().ConvertListENToModel(entradasEN).ToList();
            SessionClose();

            return View(entradasViewModel);
        }

    }
}
