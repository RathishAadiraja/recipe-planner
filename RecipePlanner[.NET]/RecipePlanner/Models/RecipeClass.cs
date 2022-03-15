using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.IO;
using System.ComponentModel.DataAnnotations;

namespace RecipePlanner.Models
{

    public class RecipeData
    {
        public string ItemName { get; set; }
        public List<Ingredient> AllIngredients { get; set; }
        
        public List<string> HowToMake { get; set; }

    }

    public class Ingredient
    {

        public string IngredName { get; set; }
        public float IngredQuant { get; set; }
        public string Unit { get; set; }

    }


    public class AddRecipe
    {
        [Required(ErrorMessage = "Please enter the food name")]
        [Display(Name = "Food name")]
        public string ARFoodName { get; set; }
        [Required(ErrorMessage = "Please enter the Ingredients")]
        [Display(Name = "Ingredients")]
        public string ARIngredients { get; set; }
        [Required(ErrorMessage = "Please enter directions to make")]
        [Display(Name = "Steps to make")]
        public string ARHowTomake { get; set; }


    }

    public class EditRecipeOne
    {
        public string ERDropDown { get; set; }
    }

    public class DeleteRecipeOne
    {
        public string DRDropDown { get; set; }
    }

    public class ItemsToCook
    {
        [Required(ErrorMessage = "Please enter the food names to cook")]
        [Display(Name = "Food names")]
        public string ITCook { get; set; }
    }

}
