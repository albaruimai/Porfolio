import { Component } from '@angular/core';
import { FormControl, FormGroup, Validators, FormBuilder } from "@angular/forms";
import { ApiService } from "../../servicios/api/api.service";
import {Credentials} from "../../modelos/response.interface";
import {Router} from "@angular/router";

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.css']
})
export class LoginComponent {

  creds: Credentials = {
    usuario: '',
    clave: ''
  };
  iniciar=true;

ngForm = new FormGroup({
  usuario: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] }),
  clave: new FormControl<string>('', { nonNullable: true, validators: [Validators.required] })
});


constructor(private api:ApiService, private router:Router) {}

   login (form: Credentials){
     this.api.login(form)
      .subscribe({
        next:response =>{
          this.iniciar = true;
          this.router.navigate(['paciente']);
          
        },
        error:error=>{
          this.iniciar = false;
        }
      })
    
   }

}
