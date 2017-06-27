﻿using CommandEverything.Framework.Util;
using CommandEverything.Framework.Util.Text;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CommandEverything.Framework.Commands
{
    /// <summary>
    /// Reads the specified file, and runs every line through this program as if the user typed it in.
    /// </summary>
    public class ExecuteScript : ICommand
    {
        public string GetHelp()
        {
            return "Runs the specified file as if the user typed in every line and pressed enter.";
        }

        public string GetName()
        {
            return "Execute Script";
        }

        public void Run(string Input)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            dlg.FileName = "Document"; // Default file name
            dlg.DefaultExt = ".txt"; // Default file extension

            // Show open file dialog box
            DialogResult result = dlg.ShowDialog();

            // Process open file dialog box results
            if (result == DialogResult.OK)
            {
                // Open document
                string[] script = File.ReadAllLines(dlg.FileName, Encoding.Default);
                this.AttemptToExecuteAll(script);
            }
            else
            {
                ConsoleWriter.WriteLine("File invalid!");
            }
        }

        /// <summary>
        /// Runs each command through the command interpreter.
        /// </summary>
        /// <param name="Inputs"></param>
        private void AttemptToExecuteAll(string[] Inputs)
        {
            foreach (string item in Inputs)
            {
                CommandInterpreter.RecieveInput(item);
            }
        }

        public bool ShouldRunThisCommand(string Input)
        {
            string[] Valid = { "execute script", "run script", "start script", "begin script" };
            return Utility.DoesStringContain(Input, Valid);
        }
    }
}