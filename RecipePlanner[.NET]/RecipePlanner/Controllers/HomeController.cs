using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Logging;
using RecipePlanner.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;

namespace RecipePlanner.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        

        public HomeController(ILogger<HomeController> logger)
        {
            _logger = logger;
        }

        public IActionResult Index()
        {
            
            return View(MakeObject.ShowInIndex());

        }
    
   
        public IActionResult AddRecipe()
        {
            return View();
        }

        [HttpPost]
        public IActionResult AddRecipe(AddRecipe addrecipeModel, string submit)
        {


            if (ModelState.IsValid)
            {
                switch (submit)
                {
                    case "Add":
                        try
                        {
                            MakeObject.DoSomething(addrecipeModel);
                        }
                        catch (Exception ex)
                        {
                            ViewBag.Error = ex;
                        }
                        return RedirectToAction("Index");
                    case "Cancel":
                        return View();

                    default:
                        return View();


                }

            }
            else
            {
                return View("AddRecipe");
            }



        }

        public IActionResult EditRecipe()
        {
            AddRecipe NewAddRecipe = MakeObject.ShowExistingData();

            return View(NewAddRecipe);
        }

        [HttpPost]
        public IActionResult EditRecipe(AddRecipe editmodel, string submit)
        {
            if (ModelState.IsValid)
            {
                switch (submit)
                {
                    case "Edit":
                        try
                        {
                            MakeObject.DoSomething(editmodel);
                        }
                        catch (Exception ex)
                        {
                            ViewBag.Error = ex;
                        }
                        return RedirectToAction("Index");
                    case "Cancel":
                        return View("EditRecipeOne");

                    default:
                        return View();


                } 

            }
            else
            {
                return View("EditRecipe");
            }
          
        }




        public IActionResult EditRecipeOne()
        {
            
            return View();
        }

        [HttpPost]
        public IActionResult EditRecipeOne(EditRecipeOne SelectedEditRecipe)
        {
            MakeObject.TrialFunc(SelectedEditRecipe);
            return RedirectToAction("EditRecipe");
        }



        public IActionResult DeleteRecipe()
        {
            
            return View();
        }

        [HttpPost]
        public IActionResult DeleteRecipe(string submit)
        {

            switch (submit) 
            {
                case "Delete":
                    MakeObject.DeleteExistingData();
                    return RedirectToAction("Index");

                case "Cancel":
                    return RedirectToAction("DeleteRecipeOne");

                default:
                    return View();


            }


        }


        public IActionResult DeleteRecipeOne()
        {

            return View();
        }

        [HttpPost]
        public IActionResult DeleteRecipeOne(DeleteRecipeOne SelectedDeleteRecipe)
        {

            MakeObject.DeleteFunc(SelectedDeleteRecipe);
            return RedirectToAction("DeleteRecipe");

        }



        public IActionResult ItemsToCook()
        {
            


            return View();
        }


        [HttpPost]
        public IActionResult ItemsToCook(ItemsToCook itemmodel)
        {
            
            if(ModelState.IsValid)
            {
                try
                {
                    MakeObject.CheckTotalIngreds(itemmodel);
                }
                catch (Exception ex)
                {
                    ViewBag.Error = ex;
                }

                return RedirectToAction("ShowAllIngredients");
            }

            return View();
        }

        public IActionResult ShowAllIngredients()
        {

            return View();
        }


        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
