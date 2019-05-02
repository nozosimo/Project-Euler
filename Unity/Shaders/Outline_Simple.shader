Shader "FastFoodFighters/BlancoMapa"
{
    Properties
    {
		_MainTex ("Textura", 2D) = "white" {}
		_Color ("Color Relleno", Color) = (1,1,1,1)
		_ColorBorde ("Color Borde", Color) = (1,1,1,1)
		_Width ("ColorRelleno", float) = 1
    }
    SubShader
    {
        
		Tags
		{
		"Queue"="Transparent"
		"IgnoreProjector"="True"
		"RenderType"="Transparent"
		"PreviewType"="Plane"
		"CanUseSpriteAtlas"="True"
		}

		Cull Off
		Lighting Off
		ZWrite Off
		Fog { Mode Off }
		Blend One OneMinusSrcAlpha

        Pass
        {
            CGPROGRAM
            #pragma vertex vert
            #pragma fragment frag

            #include "UnityCG.cginc"

            struct appdata
            {
                float4 vertex : POSITION;
                float2 uv : TEXCOORD0;
            };

            struct v2f
            {
                float2 uv : TEXCOORD0;
                float4 vertex : SV_POSITION;
            };
			fixed4 _Color;
            v2f vert (appdata v)
            {
                v2f o;
                o.vertex = UnityObjectToClipPos(v.vertex);
                o.uv = v.uv;
                return o;
            }
            sampler2D _MainTex;
			float4 _MainTex_TexelSize;
			float _Width;
			float4 _ColorBorde;

            fixed4 frag (v2f i) : SV_Target
            {
                fixed4 c = tex2D(_MainTex, i.uv);
                
			if (c.a <= 0.05)
			{
				
				//c.rgb = 0;

				c= _Color;
				// Descomentar para colorera
				//c.rgb = _ColorBorde.rgb;
				//c.a = _ColorBorde.a;
			}
			else
			{
				c.r=_Color.r;
				c.g=_Color.g;
				c.b=_Color.b;
				c.a=_Color.a;
			}

			c.rgb *= c.a;
			half4 outlineC = half4(_ColorBorde.r,_ColorBorde.g,_ColorBorde.b,_ColorBorde.a);
			outlineC.a *= ceil(c.a);
			outlineC.rgb *= outlineC.a;

			fixed alpha_up = tex2D(_MainTex, i.uv + _Width*fixed2(0, _MainTex_TexelSize.y) ).a;
			fixed alpha_down = tex2D(_MainTex, i.uv - _Width*fixed2(0, _MainTex_TexelSize.y) ).a;
			fixed alpha_right = tex2D(_MainTex, i.uv + _Width*fixed2(_MainTex_TexelSize.x, 0)).a;
			fixed alpha_left = tex2D(_MainTex, i.uv - _Width*fixed2(_MainTex_TexelSize.x, 0)).a;

			return lerp(outlineC, c, ceil(alpha_up * alpha_down * alpha_right * alpha_left));
            }
            ENDCG
        }
    }
}
