using System;

namespace DAL.Entities
{
    public class Users
    {
        public int UserId { get; set; }
        public int TIN { get; set; }
        public String Name { get; set; }
        public String UserType { get; set; }
    }
}