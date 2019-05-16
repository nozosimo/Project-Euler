using FFF.Herramientas;
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public static class CoroutineUtils 
{
    public static Coroutine StartThrowingCoroutine(this MonoBehaviour monoBehaviour,IEnumerator enumerator)
    {
        return monoBehaviour.StartCoroutine(RunThrowingIterator(enumerator));
    }

    public static IEnumerator RunThrowingIterator(IEnumerator enumerator)
    {
        while (true)
        {
            object current;
            try
            {
                if (enumerator.MoveNext() == false)
                {
                    break;
                }
                current = enumerator.Current;
            }
            catch (Exception ex)
            {
                Logs.GuardarLog(ex.ToString(), Logs.ObtenerDireccion());
                yield break;
            }
            yield return current;
        }
    }
}
