using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.IO;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.Globalization;
using System.Collections;
using System.Text.Json;
using System.Text.Json.Serialization;
using System.Text;
using System.Text.RegularExpressions;

namespace RecipePlanner.Models
{

    public class MakeObject
    {
        private const double V = 0.0;
        public static List<RecipeData> GlobalAllRecipeData = new List<RecipeData>();
        public static string EditDropDownSelectedItem;
        public static string DeleteDropDownSelectedItem;
        public static bool ForChecking = true;
        public static List<string> FinalListofIngred = new List<String>();

        public static void TrialSerialize()
        {
            string jsonString = System.Text.Json.JsonSerializer.Serialize<List<RecipeData>>(GlobalAllRecipeData);
            File.WriteAllText(ReadJson.EditPath, jsonString);
        }
        public static List<RecipeData> CheckJson()
        {

            List<RecipeData> AllRecipeData = new List<RecipeData>();

            JObject obj = JsonConvert.DeserializeObject<JObject>(ReadJson.Read());
            var properties = obj.Properties();

            foreach (var prop in properties)
            {

                List<String> Ingreds = new List<string>();
                List<object> IngredValues = new List<object>();

                RecipeData EachClass = new RecipeData();
                string Foodkey = prop.Name;
                object FoodValue = prop.Value;


                EachClass.ItemName = Foodkey;


                string InnerStr = FoodValue.ToString();
                JObject Innerobj = JsonConvert.DeserializeObject<JObject>(InnerStr);
                var InnerProperties = Innerobj.Properties();



                foreach (var p_prop in InnerProperties)
                {
                    string IngredKey = p_prop.Name;
                    object IngredValue = p_prop.Value;

                    Ingreds.Add(IngredKey);
                    IngredValues.Add(IngredValue);



                }

                List<Ingredient> EachAllIngredient = new List<Ingredient>();

                for (int i = 0; i < Ingreds.Count; i++)
                {
                    Ingredient EachIngredient = new Ingredient();


                    if (Ingreds[i] != "recipe")
                    {


                        EachIngredient.IngredName = Ingreds[i];


                        string Qunat = IngredValues[i].ToString();
                        string[] Splitted = Qunat.Split(" ");

                        EachIngredient.IngredQuant =
                            float.Parse(Splitted[0], CultureInfo.InvariantCulture.NumberFormat);
                        EachIngredient.Unit = Splitted[1];

                        EachAllIngredient.Add(EachIngredient);


                    }
                    else
                    {
                        List<string> Splitted = new List<string>();
                        IEnumerable enumerable = IngredValues[i] as IEnumerable;
                        if (enumerable != null)
                        {
                            foreach (object element in enumerable)
                            {
                                Splitted.Add(element.ToString());
                            }
                        }

                        EachClass.HowToMake = Splitted;

                    }
                }
                EachClass.AllIngredients = EachAllIngredient;


                if (AllRecipeData.Contains(EachClass))
                {
                    // Do nothing
                }
                else
                {
                    AllRecipeData.Add(EachClass);
                }

                if (GlobalAllRecipeData.Contains(EachClass))
                {
                    // Do nothing
                }
                else
                {
                    GlobalAllRecipeData.Add(EachClass);
                }




            }


            TrialSerialize();
            return AllRecipeData;
        }


        public static List<RecipeData> ShowInIndex()
        {
            if (ForChecking == true)
            {
                CheckJson();
                ForChecking = false;
            }

            return GlobalAllRecipeData;
        }



        public static void DoSomething(AddRecipe addrecipeclass)
        {


            List<Ingredient> AddIngred = new List<Ingredient>();
            List<string> AddHowToMake = new List<string>();
            RecipeData AddFinal = new RecipeData();


            AddFinal.ItemName = addrecipeclass.ARFoodName;


            string[] fornowtest = addrecipeclass.ARIngredients.Split("\n");
            List<string> Ingredarr = new List<string>();

            if (fornowtest.Length > 0)
            {

                for (int i = 0; i < fornowtest.Length; i++)
                {

                    fornowtest[i] = fornowtest[i].Replace("\n", "").Replace("\r", "");

                    if(fornowtest[i] != "")
                    {
                        
                        Ingredarr.Add(fornowtest[i].ToString());

                    }
                    

                }


            }




            if (Ingredarr.Count > 0)
            {
                foreach (string item in Ingredarr)
                {
                    
                    Ingredient AddFinalIngerd = new Ingredient();
                    string[] AName = item.Split(":");
                    AddFinalIngerd.IngredName = AName[0];



                    float v = (float)V;
                    AddFinalIngerd.IngredQuant = v;
                    string resultString = Regex.Match(AName[1], @"\d+.\d+").Value;
                    string resultString2 = Regex.Match(AName[1], @"\d+").Value;
                    if (resultString == "")
                    {
                        
                        AddFinalIngerd.IngredQuant =
                        float.Parse(resultString2, CultureInfo.InvariantCulture.NumberFormat);

                        

                    }
                    else 
                    {
                        AddFinalIngerd.IngredQuant =
                        float.Parse(resultString, CultureInfo.InvariantCulture.NumberFormat);


                    }


                    
                        
                  

                    string resultString3 = Regex.Match(AName[1], @"[a-z]+").Value;
                    if(resultString3 == "")
                    {
                        AddFinalIngerd.Unit = "default unit";

                     
                    }
                    else
                    {
                        AddFinalIngerd.Unit = resultString3;

                      
                    }




                    AddIngred.Add(AddFinalIngerd);

                }

                AddFinal.AllIngredients = AddIngred;

            }



            string[] HowMake = addrecipeclass.ARHowTomake.Split("\n");

            if (HowMake.Length > 0)
            {

                for (int i = 0; i < HowMake.Length; i++)
                {
                    
                    HowMake[i] = HowMake[i].Replace("\n", "").Replace("\r", "");

                    if (HowMake[i] != "")
                    {
                            AddHowToMake.Add(HowMake[i]);
                    }
                    

                }

                AddFinal.HowToMake = AddHowToMake;

            }

            bool Existing = false;
            foreach (var FoodInfo in GlobalAllRecipeData)
            {
          
                if (FoodInfo.ItemName == EditDropDownSelectedItem)
                {
                    Existing = true;
                    FoodInfo.ItemName = addrecipeclass.ARFoodName;
                    FoodInfo.AllIngredients = AddIngred;
                    FoodInfo.HowToMake = AddHowToMake;
                }
                else
                {
                    System.Diagnostics.Debug.WriteLine("Not equal");
                }

            }

            if (Existing == false)
            {
                GlobalAllRecipeData.Add(AddFinal);

            }

            TrialSerialize();

        }


        public static AddRecipe ShowExistingData()
        {
            string SelectedItemName = EditDropDownSelectedItem;
            AddRecipe ToBeShown = new AddRecipe();
            foreach (var item in GlobalAllRecipeData)
            {
                if (item.ItemName == SelectedItemName)
                {
                    ToBeShown.ARFoodName = item.ItemName;


                    string HowToMakeThis = "";

                    foreach (var how in item.HowToMake)
                    {
                        HowToMakeThis += how.ToString() + "\n";
                    }
                    ToBeShown.ARHowTomake = HowToMakeThis;

                    string QunatUnit = "";
                    foreach (var ingred in item.AllIngredients)
                    {
                        QunatUnit += ingred.IngredName + ":" + ingred.IngredQuant + " " + ingred.Unit + "\n";
                    }

                    ToBeShown.ARIngredients = QunatUnit;
                }
            }

            return ToBeShown;

        }




        public static string TrialFunc(EditRecipeOne TrialRecipe)
        {
            EditDropDownSelectedItem = TrialRecipe.ERDropDown;
            return TrialRecipe.ERDropDown;

        }


        public static string DeleteFunc(DeleteRecipeOne DeleteTrialRecipe)
        {

            DeleteDropDownSelectedItem = DeleteTrialRecipe.DRDropDown;
            return DeleteTrialRecipe.DRDropDown;

        }


        public static void DeleteExistingData()
        {
            foreach (var item in GlobalAllRecipeData.ToList())
            {
                if (item.ItemName == DeleteDropDownSelectedItem)
                {
                    GlobalAllRecipeData.Remove(item);
                }
            }

        }


        public static void CheckTotalIngreds(ItemsToCook itemsfromuser)
        {
            List<string> FinalList = new List<string>();

            string[] StringfromUser = itemsfromuser.ITCook.Split("\n");

            if (StringfromUser.Length > 0)
            {

                for (int i = 0; i < StringfromUser.Length; i++)
                {

                    StringfromUser[i] = StringfromUser[i].Replace("\n", "").Replace("\r", "");

                    if (StringfromUser[i] != "")
                    {
                        FinalList.Add(StringfromUser[i]);
                    }

                }

            }

            Dictionary<string, int> Mydict = new Dictionary<string, int>();

            if (FinalList.Count > 0)
            {
                

                foreach (var item in FinalList)
                {
                    if (!Mydict.ContainsKey(item.ToString()))
                    {
                        Mydict.Add(item.ToString(), 1);
                    }
                    else
                    {
                        Mydict[item.ToString()] += 1;
                    }
                }

            }


            Dictionary<string, float> FinalMydict = new Dictionary<string, float>();
            Dictionary<string, string> UnitMydict = new Dictionary<string, string>();

            foreach (var item in Mydict)
            {
                foreach(var item2 in GlobalAllRecipeData)
                {
                    if(item.Key.ToString() == item2.ItemName.ToString())
                    {
                        foreach(var ingred in item2.AllIngredients)
                        {
                            float mynum = 0;
                            mynum += ingred.IngredQuant * item.Value;

                            if (!FinalMydict.ContainsKey(ingred.IngredName))
                            {
                                
                                
                                FinalMydict.Add(ingred.IngredName, (float)Math.Round(mynum * 100f) / 100f);
                                UnitMydict.Add(ingred.IngredName, ingred.Unit);
                                
                            }
                            else
                            {
                                FinalMydict[ingred.IngredName] += (float)Math.Round(mynum * 100f) / 100f;

                            }

                            
                        }
                    }
                }
            }

            List<string> SubFinalListofIngred = new List<String>();

            foreach (var ing in FinalMydict)
            {
                string ToAdd = ing.Key + "        " + ing.Value + "  " + UnitMydict[ing.Key];
                SubFinalListofIngred.Add(ToAdd);
            }

            FinalListofIngred = SubFinalListofIngred;

            


        }



        public static class ReadJson
        {
            public static string GenPath;
            public static string EditPath;
            public static string Read()
            {
                string folpath = "wwwroot\\Jsonfile\\recipe.json";
                string editfolpath = "wwwroot\\Jsonfile\\serialised.json";
                string CurrrentDir = Directory.GetCurrentDirectory();
                string path = Path.Combine(CurrrentDir, folpath);
                GenPath = path;
                EditPath = Path.Combine(CurrrentDir, editfolpath);

                string json_text = System.IO.File.ReadAllText(path);
                return json_text;
            }

        }

    }
}