using System.Collections;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

// Gracias a: hpjohn

public class Parabola : MonoBehaviour {

    // Objeto que se mueve a lo largo de la Parabola
    public Transform Objeto; 
    // Tiempo de ese objeto
    float Tiempo = 0; 
    // Inicio y fin 
    public Transform p0, p1; 
    // Altura de la Parabola
    public float h;

    public float TiempoVuelo=5f;

    // Vectores Posicion
    private Vector3 a, b; 

    void Update()
    {
        if (p0 && p1) {
            
            // Vectores de los Puntos
            a = p0.position; 
            b = p1.position;

            if (Objeto)
            {
                Tiempo = (Time.time/ TiempoVuelo) % 1; //Completa la Parabola
                Objeto.position = fParabola(a, b, h, Tiempo);
            }
        }
    }


    // Dibuja la Parabola
    void OnDrawGizmos()
    {
        Handles.BeginGUI();
        GUI.skin.box.fontSize = 16;
        GUI.Box(new Rect(10, 10, 100, 25), h + "");
        Handles.EndGUI();

        Gizmos.color = Color.red;
        Gizmos.DrawLine(a, b);
        float count = 20;
        Vector3 UltimoPunto = a;
        for (float i = 0; i < count + 1; i++)
        {
            Vector3 p = fParabola(a, b, h, i / count);
            Gizmos.color =  Color.green;
            Gizmos.DrawLine(UltimoPunto, p);
            UltimoPunto = p;
        }
    }

    #region Parabola
 
    Vector3 fParabola(Vector3 Inicio, Vector3 Fin, float Altura, float t)
    {
        
        if (Mathf.Abs(Inicio.y - Fin.y) < 0.1f)
        {
            Vector3 travelDirection = Fin - Inicio;
            Vector3 result = Inicio + t * travelDirection;
            result.y += Mathf.Sin(t * Mathf.PI) * Altura;
            return result;
        }
        else
        {
            Vector3 DireccionViaje = Fin - Inicio;
            Vector3 DireccionNivel = Fin - new Vector3(Inicio.x, Fin.y, Inicio.z);
            Vector3 right = Vector3.Cross(DireccionViaje, DireccionNivel);
            Vector3 up = Vector3.Cross(right, DireccionNivel);
            if (Fin.y > Inicio.y) up = -up;
            Vector3 result = Inicio + t * DireccionViaje;
            result += (Mathf.Sin(t * Mathf.PI) * Altura) * up.normalized;
            return result;
        }
    }
    #endregion

}
