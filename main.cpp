#include "crow_all.h"
#include <vector>
#include <string>

struct Employee {
    std::string employeeId;
    std::string name;
    std::string city;
};

std::vector<Employee> employees;

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/greeting")([]() {
    return "Hello world!";
  });

  CROW_ROUTE(app, "/employee").name("create_employee").methods("POST"_method)([](){
   crow::json::wvalue response;

   
    auto payload = crow::json::load(crow::request_body);

    
    if (!payload) {
        response["error"] = "Invalid JSON payload";
        return crow::response(400, response);
    }

    // Extract the employee data from the payload
    Employee employee;
    employee.employeeId = payload["employeeId"].s();
    employee.name = payload["name"].s();
    employee.city = payload["city"].s();

    // Add the employee to the vector
    employees.push_back(employee);

    // Prepare the response
    response["message"] = "Employee created successfully";
    response["employee"] = employee;

    return crow::response(200, response);
  });

  CROW_ROUTE(app, "/employee/all").name("get_all_employee").methods("GET"_method)([](){
    return "";
  });

  CROW_ROUTE(app, "/employee/<string>").name("get_employee").methods("GET"_method)([](const std::string& id){
    return "";
  });

  CROW_ROUTE(app, "/employee/<string>").name("update_employee").methods("PUT"_method)([](const std::string& id){
    return "";
  });

  CROW_ROUTE(app, "/employee/<string>").name("delete_employee").methods("DELETE"_method)([](const std::string& id){
    return "";
  });

  app.port(8080).run();

  return 0;
}